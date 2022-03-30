#include "game_level.h"

#include "elements_data.h"

void game_level::load(unsigned int level_width, unsigned int level_height)
{
	//инициализация элементов
	this->level_height = level_height;
	this->level_width = level_width;

	elements.clear();
	elements.resize(level_width * level_height);
}

void game_level::simulate() const
{
	for (int i = level_width - 1; i >= 0; i--)
	{
		for (int j = level_height - 1; j >= 0; j--)
		{
			if (!get_element_at(i, j)->destroyed)
			{
				//TODO: Use id's to identify elements and do steps with them correctly
			}
		}
	}
}

void game_level::draw(sprite_renderer& renderer) const
{
	for (int i = level_width - 1; i >= 0; i--)
	{
		for (int j = level_height - 1; j >= 0; j--)
		{
			if (!get_element_at(i, j)->destroyed)
			{
				get_element_at(i, j)->draw(renderer);
			}
		}
	}
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
	return is_element_in_bounds(x, y) && elements[compute_idx(x, y)]->id == ELEMENT_EMPTY
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

element* game_level::get_element_at(const uint32_t x, const uint32_t y) const
{
	return
		elements[compute_idx(x, y)];
}

void game_level::put_element(uint32_t x, uint32_t y, element& element)
{

	if (is_element_in_bounds(x, y) && is_empty(x, y))
	{
		*elements[compute_idx(x, y)] = element;
	}

}

// Function to put pixels 
// at subsequence points 
void game_level::draw_circle(
	const int xc,
	const int yc,
	const int x, 
	const int y,
	element& element
)
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
	const int r, 
	element& element
)
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