#include "game_level.h"

#include "elements_data.h"
#include "sand.h"

void game_level::load(unsigned int level_width, unsigned int level_height)
{
	//инициализация элементов
	this->level_height = level_height;
	this->level_width = level_width;

	elements.clear();
	elements.resize(level_width * level_height);
}

void game_level::simulate()
{
	for (int i = level_width - 1; i >= 0; i--)
	{
		for (int j = level_height - 1; j >= 0; j--)
		{
			if (!is_empty(i, j))
			{
				const auto element = get_element_at(i, j);
				if (!element->destroyed)
				{
					if (element->id == 2)
					{
						update_sand(i, j);
					}
				}
			}
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
				if (!element->destroyed)
				{
					element->draw(*renderer);
				}
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
	if (get_element_at(x, y) == nullptr)
		return true;
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

void game_level::put_element(uint32_t x, uint32_t y, element* element)
{
	if (is_element_in_bounds(x, y) && is_empty(x, y))
	{
		if (element->id == 2)
			elements[compute_idx(x, y)] = element;
	}
}

// Function to put pixels 
// at subsequence points 
void game_level::draw_circle(
	const int xc,
	const int yc,
	const int x, 
	const int y,
	element* element
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
	element* element
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

void game_level::update_sand(uint32_t xpos, uint32_t ypos)
{
	if (is_element_completely_surrounded(xpos, ypos))
	{
		if (is_element_in_bounds(xpos, ypos + 1) && is_empty(xpos, ypos + 1))
		{
			get_element_at(xpos, ypos)->position = glm::vec2(xpos, ypos + 1);
			std::swap(
				elements.at(compute_idx(xpos, ypos)),
				elements.at(compute_idx(xpos, ypos + 1))
			);
			return;
		}
		if (is_element_in_bounds(xpos - 1, ypos + 1) && is_empty(xpos - 1, ypos + 1))
		{
			get_element_at(xpos, ypos)->position = glm::vec2(xpos - 1, ypos + 1);
			std::swap(
				elements.at(compute_idx(xpos - 1, ypos)),
				elements.at(compute_idx(xpos - 1, ypos))
			);
			return;
		}
		if (is_element_in_bounds(xpos - 1, ypos) && is_empty(xpos - 1, ypos))
		{
			get_element_at(xpos, ypos)->position = glm::vec2(xpos - 1, ypos);
			std::swap(
				elements.at(compute_idx(xpos - 1, ypos)),
				elements.at(compute_idx(xpos - 1, ypos))
			);
			return;
		}
		if (is_element_in_bounds(xpos + 1, ypos + 1) && is_empty(xpos + 1, ypos + 1))
		{
			get_element_at(xpos, ypos)->position = glm::vec2(xpos + 1, ypos + 1);
			std::swap(
				elements.at(compute_idx(xpos - 1, ypos)),
				elements.at(compute_idx(xpos - 1, ypos))
			);
			return;
		}
		if (is_element_in_bounds(xpos + 1, ypos) && is_empty(xpos + 1, ypos))
		{
			get_element_at(xpos, ypos)->position = glm::vec2(xpos + 1, ypos);
			std::swap(
				elements.at(compute_idx(xpos - 1, ypos)),
				elements.at(compute_idx(xpos - 1, ypos))
			);
		}
	}

}