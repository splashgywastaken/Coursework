#include "game_level.h"

#include <iostream>

#include "elements_initializer.h"
#include "sprite_renderer.h"

void game_level::load(unsigned int level_width, unsigned int level_height)
{
	//инициализация элементов
	this->level_height = level_height;
	this->level_width = level_width;

	elements_init(level_width * level_height);
}

void game_level::elements_init(const int n)
{
	if (elements != nullptr)
	{
		for (int i = 0; i < n; i++)
		{
			elements[i] = nullptr;
		}
		delete elements;
	}

	delete update_structure;

	update_structure = new bool[n];
	elements = new element_particle*[n];
	for (int i = 0; i < n; i++)
	{
		elements[i] = nullptr;
	}
}

void game_level::update_element_sim()
{
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
					update_sand(i, j);
				}
				// Если объект - вода
				else if (read_id == 2)
				{
					update_water(i, j);
				}
			}
		}
	}

	delete update_structure;
	update_structure = new bool[level_width * level_height];
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

void game_level::clear()
{
	elements_init(level_width * level_height);
}

uint32_t game_level::compute_idx(const uint32_t x, const uint32_t y) const
{
	return level_width * y + x;
}

bool game_level::is_element_in_bounds(const uint32_t x, const uint32_t y) const
{
	if (x < 0 || x > level_width - 1 || y < 0 || y > level_height - 1) return false;
	return true;
}

bool game_level::is_empty(const uint32_t x, const uint32_t y) const
{
	return is_element_in_bounds(x, y) && elements[compute_idx(x, y)] == nullptr;
}

bool game_level::is_water(uint32_t x, uint32_t y) const
{
	return
		*get_element_at(x, y)->id == 2;
}

bool game_level::is_element_completely_surrounded(uint32_t x, uint32_t y) const
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

element_particle* game_level::get_element_at(const uint32_t x, const uint32_t y) const
{
	return
		elements[compute_idx(x, y)];
}

void game_level::put_element(
	const uint32_t x, 
	const uint32_t y, 
	element_particle* element
) const
{
	if (is_element_in_bounds(x, y) && (is_empty(x, y) || element == nullptr))
	{
		elements[compute_idx(x, y)] = element;
	}
}

bool game_level::is_element_updated(uint8_t x, uint8_t y) const
{

	return update_structure[compute_idx(x, y)];

}

// Function to put pixels 
// at subsequence points 
void game_level::draw_circle(
	const int xc,
	const int yc,
	const int x, 
	const int y,
	element_particle* element
) const
{
	put_element(xc + x, yc + y, element);
	put_element(xc - x, yc + y, element);
	put_element(xc + x, yc - y, element);
	put_element(xc - x, yc - y, element);
	put_element(xc + y, yc + x, element);
	put_element(xc - y, yc + x, element);
	put_element(xc + y, yc - x, element);
	put_element(xc - y, yc - x, element);
}

// Function for circle-generation 
// using Bresenham's algorithm 
void game_level::circle_bres(
	const int xc, 
	const int yc,
	int r,
	element_particle* element
) const
{
	int x = 0, y = r;
	int d = 3 - 2 * r;
	draw_circle(
		xc, 
		yc, 
		x, 
		y, 
		element
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
			element
		);
	}
}

// TODO: Реализовать физику (симуляция через for не подходит, нужно попробовать что-то другое)
// TODO: Реализовать работу обновлений частиц (структура update_structure)
void game_level::update_sand(uint32_t xpos, uint32_t ypos) const
{
	const uint32_t element_idx = compute_idx(xpos, ypos);

	if (!is_element_updated(xpos, ypos))
		return;

	bool can_be_updated = false;
	int x_offset = 0;
	int y_offset = 0;
	const int offset = int_rand(0, 3);

	// "Просмотр вниз"
	for (int i = offset; i < 5; i++)
	{
		if (is_element_in_bounds(xpos, ypos + i) && (is_empty(xpos, ypos + i) || is_water(xpos, ypos + i)))
		{
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure[element_idx] = true;
		update_structure[compute_idx(xpos + x_offset, ypos + y_offset)] = true;

		std::swap(
			elements[element_idx],
			elements[compute_idx(xpos + x_offset, ypos + y_offset)]
		);

		return;
	}

	// Просмотр по диоганали в левую сторону
	for (int i = offset; i < 3; i++)
	{
		if (is_element_in_bounds(xpos - i, ypos + i) && (is_empty(xpos - i, ypos + i) || is_water(xpos - i, ypos + i)))
		{
			x_offset = -i;
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure[element_idx] = true;
		update_structure[compute_idx(xpos + x_offset, ypos + y_offset)] = true;

		std::swap(
			elements[element_idx],
			elements[compute_idx(xpos + x_offset, ypos + y_offset)]
		);

		return;
	}

	// Просмотр по диоганали в правую сторону
	for (int i = offset; i < 3; i++)
	{
		if (is_element_in_bounds(xpos + i, ypos + i) && (is_empty(xpos + i, ypos + i) || is_water(xpos + i, ypos + i)))
		{
			x_offset = i;
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure[element_idx] = true;
		update_structure[compute_idx(xpos + x_offset, ypos + y_offset)] = true;

		std::swap(
			elements[element_idx],
			elements[compute_idx(xpos + x_offset, ypos + y_offset)]
		);
	}

}

void game_level::update_water(uint32_t xpos, uint32_t ypos) const
{
	const uint32_t element_idx = compute_idx(xpos, ypos);

	if (!is_element_updated(xpos, ypos))
		return;

	bool can_be_updated = false;
	int x_offset = 0;
	int y_offset = 0;
	const int offset = int_rand(0, 3);

	// "Просмотр вниз"
	for (int i = offset; i < 5; i++)
	{
		if (is_element_in_bounds(xpos, ypos + i) && is_empty(xpos, ypos + i))
		{
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure[element_idx] = true;
		update_structure[compute_idx(xpos, ypos + y_offset)] = true;

		std::swap(
			elements[element_idx],
			elements[compute_idx(xpos, ypos + y_offset)]
		);

		return;
	}

	// Просмотр по диагонали в левую сторону
	for (int i = offset; i < 3; i++)
	{
		if (is_element_in_bounds(xpos - i, ypos + i) && is_empty(xpos - i, ypos + i))
		{
			x_offset = -i;
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure[element_idx] = true;
		update_structure[compute_idx(xpos + x_offset, ypos + y_offset)] = true;

		std::swap(
			elements[element_idx],
			elements[compute_idx(xpos + x_offset, ypos + y_offset)]
		);

		return;
	}

	// Просмотр в левую сторону
	for (int i = offset; i < 5; i++)
	{
		if (is_element_in_bounds(xpos - i, ypos) && is_empty(xpos - i, ypos))
		{
			x_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure[element_idx] = true;
		update_structure[compute_idx(xpos - x_offset, ypos)] = true;

		std::swap(
			elements[element_idx],
			elements[compute_idx(xpos - x_offset, ypos)]
		);

		return;
	}

	// Просмотр по диагонали в правую сторону
	for (int i = offset; i < 3; i++)
	{
		if (is_element_in_bounds(xpos + i, ypos + i) && is_empty(xpos + i, ypos + i))
		{
			x_offset = i;
			y_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure[element_idx] = true;
		update_structure[compute_idx(xpos + x_offset, ypos + y_offset)] = true;

		std::swap(
			elements[element_idx],
			elements[compute_idx(xpos + x_offset, ypos + y_offset)]
		);

		return;
	}

	// Просмотр в правую сторону
	for (int i = offset; i < 5; i++)
	{
		if (is_element_in_bounds(xpos + i, ypos) && is_empty(xpos + i, ypos))
		{
			x_offset = i;
			can_be_updated = true;
		}
	}

	if (can_be_updated)
	{
		update_structure[element_idx] = true;
		update_structure[compute_idx(xpos + x_offset, ypos)] = true;

		std::swap(
			elements[element_idx],
			elements[compute_idx(xpos + x_offset, ypos)]
		);

		return;
	}
}
