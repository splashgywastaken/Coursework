#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H
#include <vector>

#include "element.h"

class game_level
{
public:
	// ������� ���������
	std::vector<element*> elements;
	unsigned int level_width = 0;
	unsigned int level_height = 0;

	// �����������
	game_level() = default;

	// �������� ������
	void load(unsigned int level_width, unsigned int level_height);

	// ��� ��� ������ ���������
	void simulate();

	// ������ ������
	void draw(sprite_renderer* renderer) const;

	// ��������� ������� ��������
	uint32_t compute_idx(uint32_t x, uint32_t y) const;

	// ��������� �������� �� ��������� ��������:
	element* get_element_at(uint32_t x, uint32_t y) const;

	// �������� �� �������������� ������� �����������
	bool is_element_in_bounds(uint32_t x, uint32_t y) const;

	// �������� �� ������� ������
	bool is_empty(uint32_t x, uint32_t y) const;

	// �������� �� ��, ��������� �� ������� �������
	bool is_element_completely_surrounded(uint32_t x, uint32_t y) const;

	// ��������� ������� element �� ���������� � � �
	void put_element(uint32_t x, uint32_t y, element* element);

	// ����� ��� ��������� �������� �� ������������ �����
	void draw_circle(
		const int xc,
		const int yc,
		const int x,
		const int y,
		element* element
	);

	// ����� ���������� ���������� �� ������ ����������
	void circle_bres(
		const int xc,
		const int yc,
		const int r,
		element* element
	);

	void update_sand(uint32_t xpos, uint32_t ypos);

	//TODO: �������� ������ �� ���������� ��������� ��������� � �����
};
#endif