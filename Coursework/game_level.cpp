// ReSharper disable CppClangTidyClangDiagnosticImplicitIntConversion
// ReSharper disable CppClangTidyCppcoreguidelinesNarrowingConversions
#include "game_level.h"

#include <iostream>

#include "elements_initializer.h"
#include "sprite_renderer.h"

void game_level::load(const int input_level_width, const int input_level_height)
{
	//инициализация элементов
	this->level_height = input_level_height;
	this->level_width = input_level_width;

	elements_init();
}

void game_level::elements_init()
{
	const int n = level_height * level_width;

	update_structure = new bool[n];
	elements = new std::vector<element_particle*>;
	elements->resize(n);
	for (int i = 0; i < n; i++)
	{
		elements->at(i) = new element_particle(elements_initializer::empty());
	}
}

void game_level::update_element_sim(float dt) const
{
	bool chunk_was_updated = false;

	for (int i = level_width - 1; i >= 0; i--)
	{
		for (int j = level_height - 1; j >= 0; j--)
		{
			if (!is_empty(i, j))
			{
				const int read_id = *get_element_at(i, j)->id;
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
				else if (read_id == 3)
				{
					chunk_was_updated = update_stone(i, j);
				}
			}
		}
	}
	
	for (short int i = 0; i < level_width - 1; i++)
	{
		for (short int j = 0; j < level_height - 1; j++)
		{
			update_structure[compute_idx(i, j)] = !update_structure[compute_idx(i, j)];
		}
	}
}

void game_level::draw(sprite_renderer* renderer) const
{
	for (int i = level_width - 1; i >= 0; i--)
	{
		for (int j = level_height - 1; j >= 0; j--)
		{
			if (!is_empty(i, j))
			{
				const auto element = get_element_at(i, j);
				renderer->draw_sprite(
					glm::vec2(i, j),
					glm::vec2(elements_size),
					0,
					*element->color
				);
			}
		}
	}
}

void game_level::clear() const
{
	const int n = level_height * level_width;
	
	for (int i = 0; i < n; i++)
	{
		delete elements->at(i);
	}
	delete elements;
	delete update_structure;
}

int game_level::compute_idx(const int x, const int y) const
{
	return level_width * y + x;
}

bool game_level::is_element_in_bounds(const int& x, const int& y) const
{
	if (x < 0 || x > level_width - 1 || y < 0 || y > level_height - 1) return false;
	return true;
}

bool game_level::is_empty(const int& x, const int& y) const
{
	return is_element_in_bounds(x, y) && get_element_at(x, y)->id == nullptr;
}

bool game_level::is_water(const int& x, const int& y) const
{
	return
		*get_element_at(x, y)->id == 2;
}

bool game_level::is_element_completely_surrounded(const int x, const int y) const
{
	// Top
	if (is_element_in_bounds(x, y - 1) && !is_empty(x, y - 1)) {
		return false;
	}
	// Bottom
	if (is_element_in_bounds(x, y + 1) && !is_empty(x, y + 1)) {
		return false;
	}
	// Left
	if (is_element_in_bounds(x - 1, y) && !is_empty(x - 1, y)) {
		return false;
	}
	// Right
	if (is_element_in_bounds(x + 1, y) && !is_empty(x + 1, y)) {
		return false;
	}
	// Top Left
	if (is_element_in_bounds(x - 1, y - 1) && !is_empty(x - 1, y - 1)) {
		return false;
	}
	// Top Right
	if (is_element_in_bounds(x + 1, y - 1) && !is_empty(x + 1, y - 1)) {
		return false;
	}
	// Bottom Left
	if (is_element_in_bounds(x - 1, y + 1) && !is_empty(x - 1, y + 1)) {
		return false;
	}
	// Bottom Right
	if (is_element_in_bounds(x + 1, y + 1) && !is_empty(x + 1, y + 1)) {
		return false;
	}

	return true;
}

element_particle* game_level::get_element_at(const int& x, const int& y) const
{
	return
		elements->at(compute_idx(x, y));
}

void game_level::put_element(
	const short int& x,
	const short int& y,
	const short int& element_id
) const
{
	if (is_element_in_bounds(x, y) && (is_empty(x, y) || element_id == 0))
	{
		switch (element_id)
		{
		case 0:
			elements->at(compute_idx(x, y)) = new element_particle(elements_initializer::empty());
			break;
		case 1:
			elements->at(compute_idx(x, y)) = new element_particle(elements_initializer::sand());
			break;
		case 2:
			elements->at(compute_idx(x, y)) = new element_particle(elements_initializer::water());
			break;
		case 3:
			elements->at(compute_idx(x, y)) = new element_particle(elements_initializer::stone());
			break;
		default: ;
		}
	}	
}

bool game_level::is_element_updated(const int& x, const int& y) const
{

	return update_structure[compute_idx(x, y)];

}

// Function to put pixels 
// at subsequence points 
void game_level::draw_circle(
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

void game_level::circle_bres(
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
		// For each pixel we will 
		// draw all eight pixels
		x++;

		// Check for decision parameter 
		// and correspondingly  
		// update d, x, y 
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

void game_level::draw_circle(
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

void game_level::put_pixel(const int x, const int y, sprite_renderer* renderer)
{
	renderer->draw_sprite(
		glm::vec2(x, y),
		glm::vec2(1.0f)
	);
}

// Function for circle-generation 
// using Bresenham's algorithm 
void game_level::circle_bres(
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
		// For each pixel we will 
		// draw all eight pixels
		x++;

		// Check for decision parameter 
		// and correspondingly  
		// update d, x, y 
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

// TODO: Реализовать 

bool game_level::update_sand(const int x_position, const int y_position) const
{

	if (!is_element_updated(x_position, y_position))
		return true;

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
		update_structure[element_idx] = true;
		update_structure[compute_idx(x_position, y_position + y_offset)] = true;

		std::swap(
			elements->at(compute_idx(x_position, y_position)),
			elements->at(compute_idx(x_position, y_position + y_offset))
		);

		return true;
	}

	// Просмотр по диоганали в левую сторону
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
		update_structure[element_idx] = true;
		update_structure[compute_idx(x_position - x_offset, y_position + y_offset)] = true;

		std::swap(
			elements->at(compute_idx(x_position, y_position)),
			elements->at(compute_idx(x_position - x_offset, y_position + y_offset))
		);

		return true;
	}

	// Просмотр по диоганали в правую сторону
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
		update_structure[element_idx] = true;
		update_structure[compute_idx(x_position + x_offset, y_position + y_offset)] = true;

		std::swap(
			elements->at(compute_idx(x_position, y_position)),
			elements->at(compute_idx(x_position + x_offset, y_position + y_offset))
		);

		return true;
	}

	return false;
}

bool game_level::update_water(const int x_position, const int y_position) const
{

	if (!is_element_updated(x_position, y_position))
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
			&& is_empty(x_position, y_position + i)
			)
		{
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure[element_idx] = true;
		update_structure[compute_idx(x_position, y_position + y_offset)] = true;
		
		std::swap(
			elements->at(compute_idx(x_position, y_position)),
			elements->at(compute_idx(x_position, y_position + y_offset))
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
		update_structure[element_idx] = true;
		update_structure[compute_idx(x_position - x_offset, y_position + y_offset)] = true;

		std::swap(
			elements->at(compute_idx(x_position, y_position)),
			elements->at(compute_idx(x_position - x_offset, y_position + y_offset))
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
		update_structure[element_idx] = true;
		update_structure[compute_idx(x_position - x_offset, y_position)] = true;

		std::swap(
			elements->at(compute_idx(x_position, y_position)),
			elements->at(compute_idx(x_position - x_offset, y_position))
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
		update_structure[element_idx] = true;
		update_structure[compute_idx(x_position + x_offset, y_position + y_offset)] = true;

		std::swap(
			elements->at(compute_idx(x_position, y_position)),
			elements->at(compute_idx(x_position + x_offset, y_position + y_offset))
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
		update_structure[element_idx] = true;
		update_structure[compute_idx(x_position + x_offset, y_position)] = true;
		
		std::swap(
			elements->at(compute_idx(x_position, y_position)),
			elements->at(compute_idx(x_position + x_offset, y_position + y_offset))
		);

		return true;
	}

	return false;
}

bool game_level::update_stone(int x_position, int y_position) const
{

	return true;

}

bool game_level::update_salt(int x_position, int y_position)
{

	return true;

}
