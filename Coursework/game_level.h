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
	void simulate() const;

	// ������ ������
	void draw(sprite_renderer& renderer) const;

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
	void put_element(uint32_t x, uint32_t y, element& element);

	// ����� ��� ��������� �������� �� ������������ �����
	void draw_circle(
		int xc,
		int yc,
		int x,
		int y,
		element& element
	);

	// ����� ���������� ���������� �� ������ ����������
	void circle_bres(
		int xc,
		int yc,
		int r,
		element& element
	);

	//TODO: �������� ������ �� ���������� ��������� ��������� � �����
};
#endif