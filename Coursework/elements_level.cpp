#include "elements_level.h"
#include "elements_initializer.h"
#include "sprite_renderer.h"

void elements_level::load(const int input_level_width, const int input_level_height)
{
	//инициализация элементов
	this->level_height_ = input_level_height + 1;
	this->level_width_ = input_level_width + 1;

	elements_init();
}

void elements_level::elements_init()
{
	const int n = level_height_ * level_width_;

	update_structure_ = new bool[n];
	elements_ = new std::vector<element_particle*>;
	elements_->resize(n);
	for (int i = 0; i < n; i++)
	{
		elements_->at(i) = nullptr;
	}
}

void elements_level::update_element_level(float dt) const
{
	for (int i = level_width_ - 1; i >= 0; i--)
	{
		for (int j = level_height_ - 1; j >= 0; j--)
		{
			if (!is_empty(i, j))
			{
				const element_particle* read_element = get_element_at(i, j);
				if (read_element != nullptr)
				{
					bool chunk_was_updated = false;
					const int read_id = *read_element->id;
					//Если объект - песок
					if (read_id == 1)
					{
						chunk_was_updated = update_sand(i, j);
					}
					// Если объект - вода
					else if (read_id == 2)
					{
						chunk_was_updated = update_water(i, j);
					}
					//// Если объект - камень
					//else if (read_id == 3)
					//{
					//	chunk_was_updated = update_stone(i, j);
					//}
					// Если объект - соль
					else if (read_id == 4)
					{
						chunk_was_updated = update_salt(i, j);
					}
					// Если объект - огонь
					else if (read_id == 5)
					{
						chunk_was_updated = update_fire(i, j);
					}
					// Если объект - дерево
					else if (read_id == 6)
					{
						chunk_was_updated = update_wood(i, j);
					}
				}
			}
		}
	}
	
	for (short int i = 0; i < level_width_ - 1; i++)
	{
		for (short int j = 0; j < level_height_ - 1; j++)
		{
			update_structure_[compute_idx(i, j)] = !update_structure_[compute_idx(i, j)];
		}
	}
}

void elements_level::draw(sprite_renderer* renderer) const
{
	for (int i = level_width_ - 1; i >= 0; i--)
	{
		for (int j = level_height_ - 1; j >= 0; j--)
		{
			if (!is_empty(i, j))
			{
				const auto element = get_element_at(i, j);
				renderer->draw_sprite(
					glm::vec2(i, j),
					glm::vec2(1.f),
					*element->color
				);
			}
		}
	}
}

void elements_level::clear() const
{
	const int n = level_height_ * level_width_;
	
	for (int i = 0; i < n; i++)
	{
		delete elements_->at(i);
	}
	delete elements_;
	delete update_structure_;
}

int elements_level::compute_idx(const int x, const int y) const
{
	return level_width_ * y + x;
}

bool elements_level::is_element_in_bounds(const int& x, const int& y) const
{
	if (x < 0 || x > level_width_ - 1 || y < 0 || y > level_height_ - 1) return false;
	return true;
}

bool elements_level::is_solid(const int& x, const int& y) const
{
	if (get_element_at(x, y) != nullptr)
		return
		*get_element_at(x, y)->type == 0;
	return false;
}

bool elements_level::is_gas(const int& x, const int& y) const
{
	if (get_element_at(x, y) != nullptr)
		return
		*get_element_at(x, y)->type == 3;
	return false;
}

bool elements_level::is_empty(const int& x, const int& y) const
{
	return is_element_in_bounds(x, y) && get_element_at(x, y) == nullptr;
}

bool elements_level::is_water(const int& x, const int& y) const
{
	if (get_element_at(x, y) != nullptr)
		return
			*get_element_at(x, y)->id == 2;
	return false;
}

bool elements_level::is_fire(const int& x, const int& y) const
{
	if (get_element_at(x, y) != nullptr)
		return
		*get_element_at(x, y)->id == 5;
	return false;
}

bool elements_level::is_completely_surrounded(const int x, const int y) const
{
	// Верх
	if (is_element_in_bounds(x, y - 1) && is_empty(x, y - 1)) {
		return false;
	}
	// Низ
	if (is_element_in_bounds(x, y + 1) && is_empty(x, y + 1)) {
		return false;
	}
	// Лево
	if (is_element_in_bounds(x - 1, y) && is_empty(x - 1, y)) {
		return false;
	}
	// Право
	if (is_element_in_bounds(x + 1, y) && is_empty(x + 1, y)) {
		return false;
	}
	// Лево верх
	if (is_element_in_bounds(x - 1, y - 1) && is_empty(x - 1, y - 1)) {
		return false;
	}
	// Лево право
	if (is_element_in_bounds(x + 1, y - 1) && is_empty(x + 1, y - 1)) {
		return false;
	}
	// Низ лево
	if (is_element_in_bounds(x - 1, y + 1) && is_empty(x - 1, y + 1)) {
		return false;
	}
	// Низ право
	if (is_element_in_bounds(x + 1, y + 1) && is_empty(x + 1, y + 1)) {
		return false;
	}

	return true;
}

bool elements_level::is_completely_surrounded_by_solid(const int x, const int y) const
{
	// Верх
	if (is_element_in_bounds(x, y - 1) && !is_solid(x, y - 1)) {
		return false;
	}
	// Низ
	if (is_element_in_bounds(x, y + 1) && !is_solid(x, y + 1)) {
		return false;
	}
	// Лево
	if (is_element_in_bounds(x - 1, y) && !is_solid(x - 1, y)) {
		return false;
	}
	// Право
	if (is_element_in_bounds(x + 1, y) && !is_solid(x + 1, y)) {
		return false;
	}
	// Лево верх
	if (is_element_in_bounds(x - 1, y - 1) && !is_solid(x - 1, y - 1)) {
		return false;
	}
	// Лево право
	if (is_element_in_bounds(x + 1, y - 1) && !is_solid(x + 1, y - 1)) {
		return false;
	}
	// Низ лево
	if (is_element_in_bounds(x - 1, y + 1) && !is_solid(x - 1, y + 1)) {
		return false;
	}
	// Низ право
	if (is_element_in_bounds(x + 1, y + 1) && !is_solid(x + 1, y + 1)) {
		return false;
	}

	return true;
}

bool elements_level::is_near_water(const int x, const int y) const
{
	// Верх
	if (is_element_in_bounds(x, y - 1) && !is_empty(x, y - 1)) {
		if (is_water(x, y - 1))
		{
			return true;
		}
	}
	// Низ
	if (is_element_in_bounds(x, y + 1) && !is_empty(x, y + 1)) {
		if (is_water(x, y + 1))
		{
			return true;
		}
	}
	// Лево
	if (is_element_in_bounds(x - 1, y) && !is_empty(x - 1, y)) {
		if (is_water(x - 1, y))
		{
			return true;
		}
	}
	// Право
	if (is_element_in_bounds(x + 1, y) && !is_empty(x + 1, y)) {
		if (is_water(x + 1, y))
		{
			return true;
		}
	}
	// Лево верх
	if (is_element_in_bounds(x - 1, y - 1) && !is_empty(x - 1, y - 1)) {
		if (is_water(x - 1, y - 1))
		{
			return true;
		}
	}
	// Лево право
	if (is_element_in_bounds(x + 1, y - 1) && !is_empty(x + 1, y - 1)) {
		if (is_water(x + 1, y - 1))
		{
			return true;
		}
	}
	// Низ лево
	if (is_element_in_bounds(x - 1, y + 1) && !is_empty(x - 1, y + 1)) {
		if (is_water(x - 1, y + 1))
		{
			return true;
		}
	}
	// Низ право
	if (is_element_in_bounds(x + 1, y + 1) && !is_empty(x + 1, y + 1)) {
		if (is_water(x + 1, y + 1))
		{
			return true;
		}
	}

	return false;
}

bool elements_level::is_near_fire(const int x, const int y) const
{
	// Верх
	if (is_element_in_bounds(x, y - 1) && !is_empty(x, y - 1)) {
		if (is_fire(x, y - 1))
		{
			return true;
		}
	}
	// Низ
	if (is_element_in_bounds(x, y + 1) && !is_empty(x, y + 1)) {
		if (is_fire(x, y + 1))
		{
			return true;
		}
	}
	// Лево
	if (is_element_in_bounds(x - 1, y) && !is_empty(x - 1, y)) {
		if (is_fire(x - 1, y))
		{
			return true;
		}
	}
	// Право
	if (is_element_in_bounds(x + 1, y) && !is_empty(x + 1, y)) {
		if (is_fire(x + 1, y))
		{
			return true;
		}
	}
	// Лево верх
	if (is_element_in_bounds(x - 1, y - 1) && !is_empty(x - 1, y - 1)) {
		if (is_fire(x - 1, y - 1))
		{
			return true;
		}
	}
	// Лево право
	if (is_element_in_bounds(x + 1, y - 1) && !is_empty(x + 1, y - 1)) {
		if (is_fire(x + 1, y - 1))
		{
			return true;
		}
	}
	// Низ лево
	if (is_element_in_bounds(x - 1, y + 1) && !is_empty(x - 1, y + 1)) {
		if (is_fire(x - 1, y + 1))
		{
			return true;
		}
	}
	// Низ право
	if (is_element_in_bounds(x + 1, y + 1) && !is_empty(x + 1, y + 1)) {
		if (is_fire(x + 1, y + 1))
		{
			return true;
		}
	}

	return false;
}

element_particle* elements_level::get_element_at(const int& x, const int& y) const
{
	return
		elements_->at(compute_idx(x, y));
}

void elements_level::delete_element_at(const int& x, const int& y) const
{
	elements_->at(compute_idx(x, y)) = nullptr;
}

void elements_level::put_element(
	const int& x,
	const int& y,
	const int& element_id
) const
{
	if (is_element_in_bounds(x, y) && (is_empty(x, y) || element_id == 0))
	{
		switch (element_id)
		{
		case 0:
			elements_->at(compute_idx(x, y)) = nullptr;
			break;
		case 1:
			elements_->at(compute_idx(x, y)) = new element_particle(elements_initializer::sand());
			break;
		case 2:
			elements_->at(compute_idx(x, y)) = new element_particle(elements_initializer::water());
			break;
		case 3:
			elements_->at(compute_idx(x, y)) = new element_particle(elements_initializer::stone());
			break;
		case 4:
			elements_->at(compute_idx(x, y)) = new element_particle(elements_initializer::salt());
			break;
		case 5:
			elements_->at(compute_idx(x, y)) = new element_particle(elements_initializer::fire());
			break;
		case 6:
			elements_->at(compute_idx(x, y)) = new element_particle(elements_initializer::wood());
			break;
		default: ;
		}
	}	
}

bool elements_level::is_element_updated(const int& x, const int& y) const
{

	return update_structure_[compute_idx(x, y)];

}

// Функция для установки пикселей 
// на определенные точки
void elements_level::draw_circle(
	const int& xc,
	const int& yc,
	const int& x, 
	const int& y,
	const int& element_id
) const
{
	put_element(xc + x, yc + y, element_id);
	put_element(xc - x, yc + y, element_id);
	put_element(xc + x, yc - y, element_id);
	put_element(xc - x, yc - y, element_id);
	put_element(xc + y, yc + x, element_id);
	put_element(xc - y, yc + x, element_id);
	put_element(xc + y, yc - x, element_id);
	put_element(xc - y, yc - x, element_id);
}

void elements_level::circle_bres(
	const int xc,
	const int yc,
	const int brush_radius, 
	sprite_renderer *renderer
) const
{
	int x = 0, y = brush_radius;
	int d = 3 - 2 * brush_radius;
	draw_circle(
		xc,
		yc,
		x,
		y,
		renderer
	);
	while (y >= x)
	{
		x++;
		
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		draw_circle(
			xc,
			yc,
			x,
			y,
			renderer
		);
	}
}

void elements_level::draw_circle(
	const int xc, 
	const int yc, 
	const int x,
	const int y, 
	sprite_renderer* renderer
)
{
	put_pixel(xc + x, yc + y, renderer);
	put_pixel(xc - x, yc + y, renderer);
	put_pixel(xc + x, yc - y, renderer);
	put_pixel(xc - x, yc - y, renderer);
	put_pixel(xc + y, yc + x, renderer);
	put_pixel(xc - y, yc + x, renderer);
	put_pixel(xc + y, yc - x, renderer);
	put_pixel(xc - y, yc - x, renderer);
}

void elements_level::put_pixel(const int x, const int y, sprite_renderer* renderer)
{
	renderer->draw_sprite(
		glm::vec2(x, y),
		glm::vec2(1.0f)
	);
}

void elements_level::circle_bres(
	const int xc, 
	const int yc,
	const int r,
	const int element_id
) const
{
	int x = 0, y = r;
	int d = 3 - 2 * r;
	draw_circle(
		xc, 
		yc, 
		x, 
		y, 
		element_id
	);
	while (y >= x)
	{
		// Для каждого пикселя мы
		// отрисуем все 8 пикселей
		x++;

		// Проверка на параметр выбора 
		// и соответственно
		// обновляем d, x, y
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		draw_circle(
			xc, 
			yc, 
			x, 
			y, 
			element_id
		);
	}
}

bool elements_level::update_sand(const int x_position, const int y_position) const
{
	if (!is_element_updated(x_position, y_position))
	{
		return true;
	}

	if (is_completely_surrounded(x_position, y_position))
	{
		if (is_completely_surrounded_by_solid(x_position, y_position))
		{
			return true;
		}
	}

	const uint32_t element_idx = compute_idx(x_position, y_position);
	bool can_be_updated = false;
	int x_offset = 0;
	int y_offset = 0;
	const int offset = int_rand(0, 4);

	// "Просмотр вниз"
	for (int i = offset; i < 5; i++)
	{
		if (
			is_element_in_bounds(x_position, y_position + i) 
			&& (is_empty(x_position, y_position + i) 
				|| is_water(x_position, y_position + i))
			)
		{
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure_[element_idx] = true;
		update_structure_[compute_idx(x_position, y_position + y_offset)] = true;

		std::swap(
			elements_->at(element_idx),
			elements_->at(compute_idx(x_position, y_position + y_offset))
		);

		return true;
	}

	// Просмотр по диагонали в левую сторону
	for (int i = offset; i < 3; i++)
	{
		if (
			is_element_in_bounds(x_position - i, y_position + i)
			&& is_empty(x_position - i, y_position + i)
			)
		{
			x_offset = i;
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure_[element_idx] = true;
		update_structure_[compute_idx(x_position - x_offset, y_position + y_offset)] = true;

		std::swap(
			elements_->at(element_idx),
			elements_->at(compute_idx(x_position - x_offset, y_position + y_offset))
		);

		return true;
	}

	// Просмотр по диагонали в правую сторону
	for (int i = offset; i < 3; i++)
	{
		if (
			is_element_in_bounds(x_position + i, y_position + i) 
			&& is_empty(x_position + i, y_position + i)
			)
		{
			x_offset = i;
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure_[element_idx] = true;
		update_structure_[compute_idx(x_position + x_offset, y_position + y_offset)] = true;

		std::swap(
			elements_->at(element_idx),
			elements_->at(compute_idx(x_position + x_offset, y_position + y_offset))
		);

		return true;
	}

	return false;
}

bool elements_level::update_water(const int x_position, const int y_position) const
{
	if (!is_element_updated(x_position, y_position))
		return true;

	if (is_completely_surrounded(x_position, y_position))
		return true;

	bool can_be_updated = false;
	int x_offset = 0;
	int y_offset = 0;
	const uint32_t element_idx = compute_idx(x_position, y_position);
	const int offset = int_rand(0, 6);

	// "Просмотр вниз"
	for (int i = offset; i < 7; i++)
	{
		if (
			is_element_in_bounds(x_position, y_position + i)
			&& (is_empty(x_position, y_position + i) || is_gas(x_position, y_position + i))
			)
		{
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure_[element_idx] = true;
		update_structure_[compute_idx(x_position, y_position + y_offset)] = true;
		
		std::swap(
			elements_->at(element_idx),
			elements_->at(compute_idx(x_position, y_position + y_offset))
		);
		
		return true;
	}

	// Просмотр по диагонали в левую сторону
	for (int i = offset; i < 7; i++)
	{
		if (
			is_element_in_bounds(x_position - i, y_position + i) 
			&& is_empty(x_position - i, y_position + i)
			)
		{
			x_offset = i;
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure_[element_idx] = true;
		update_structure_[compute_idx(x_position - x_offset, y_position + y_offset)] = true;

		std::swap(
			elements_->at(element_idx),
			elements_->at(compute_idx(x_position - x_offset, y_position + y_offset))
		);

		return true;
	}

	// Просмотр в левую сторону
	for (int i = offset; i < 9; i++)
	{
		if (is_element_in_bounds(x_position - i, y_position) && is_empty(x_position - i, y_position))
		{
			x_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure_[element_idx] = true;
		update_structure_[compute_idx(x_position - x_offset, y_position)] = true;

		std::swap(
			elements_->at(element_idx),
			elements_->at(compute_idx(x_position - x_offset, y_position))
		);

		return true;
	}

	// Просмотр по диагонали в правую сторону
	for (int i = offset; i < 7; i++)
	{
		if (is_element_in_bounds(x_position + i, y_position + i) && is_empty(x_position + i, y_position + i))
		{
			x_offset = i;
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure_[element_idx] = true;
		update_structure_[compute_idx(x_position + x_offset, y_position + y_offset)] = true;

		std::swap(
			elements_->at(element_idx),
			elements_->at(compute_idx(x_position + x_offset, y_position + y_offset))
		);

		return true;
	}

	// Просмотр в правую сторону
	for (int i = offset; i < 9; i++)
	{
		if (is_element_in_bounds(x_position + i, y_position) && is_empty(x_position + i, y_position))
		{
			x_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure_[element_idx] = true;
		update_structure_[compute_idx(x_position + x_offset, y_position)] = true;
		
		std::swap(
			elements_->at(element_idx),
			elements_->at(compute_idx(x_position + x_offset, y_position + y_offset))
		);

		return true;
	}

	return false;
}

bool elements_level::update_stone(const int x_position, const int y_position) const
{
	
	return false;

}

bool elements_level::update_salt(const int x_position, const int y_position) const
{
	if (!is_element_updated(x_position, y_position))
	{
		return true;
	}

	if (is_completely_surrounded(x_position, y_position))
	{
		if (is_near_water(x_position, y_position))
		{
			if (int_rand(0, 10) == 1)
			{
				delete_element_at(x_position, y_position);
			}
			return true;
		}
	}

	const uint32_t element_idx = compute_idx(x_position, y_position);
	bool can_be_updated = false;
	int x_offset = 0;
	int y_offset = 0;
	const int offset = int_rand(0, 4);

	// "Просмотр вниз"
	for (int i = offset; i < 5; i++)
	{
		if (
			is_element_in_bounds(x_position, y_position + i)
			&& (is_empty(x_position, y_position + i)
				|| is_water(x_position, y_position + i))
			)
		{
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure_[element_idx] = true;
		update_structure_[compute_idx(x_position, y_position + y_offset)] = true;

		std::swap(
			elements_->at(element_idx),
			elements_->at(compute_idx(x_position, y_position + y_offset))
		);

		return true;
	}

	// Просмотр по диагонали в левую сторону
	for (int i = offset; i < 3; i++)
	{
		if (
			is_element_in_bounds(x_position - i, y_position + i)
			&& is_empty(x_position - i, y_position + i)
			)
		{
			x_offset = i;
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure_[element_idx] = true;
		update_structure_[compute_idx(x_position - x_offset, y_position + y_offset)] = true;

		std::swap(
			elements_->at(element_idx),
			elements_->at(compute_idx(x_position - x_offset, y_position + y_offset))
		);

		return true;
	}

	// Просмотр по диагонали в правую сторону
	for (int i = offset; i < 3; i++)
	{
		if (
			is_element_in_bounds(x_position + i, y_position + i)
			&& is_empty(x_position + i, y_position + i)
			)
		{
			x_offset = i;
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure_[element_idx] = true;
		update_structure_[compute_idx(x_position + x_offset, y_position + y_offset)] = true;

		std::swap(
			elements_->at(element_idx),
			elements_->at(compute_idx(x_position + x_offset, y_position + y_offset))
		);

		return true;
	}

	return false;
}

bool elements_level::update_fire(const int x_position, const int y_position) const
{
	if (!is_element_updated(x_position, y_position))
	{
		return true;
	}

	// Шанс потушить огонь водой (шанс настолько большой что огонь в любом случае потухнет)
	if (is_near_water(x_position, y_position))
	{
		if (int_rand(0, 1) == 0)
		{
			delete_element_at(x_position, y_position);
		}
	}

	// Шанс потухнуть
	if (int_rand(0, 9) == 0)
	{
		delete_element_at(x_position, y_position);
	}
	return true;
}

bool elements_level::update_wood(const int x_position, const int y_position) const
{
	if (is_near_fire(x_position, y_position))
	{
		if (int_rand(0, 19) == 0)
		{
			// С шансом 20% дерево загорается и становится либо огнем либо дымом
			delete_element_at(x_position, y_position);
			elements_->at(compute_idx(x_position, y_position))
				= new element_particle(elements_initializer::fire());

			return true;
		}
	}

	return false;
}