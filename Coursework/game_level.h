#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <random>

#include "element_particle.h"
#include "sprite_renderer.h"

class game_level
{
public:
	// ������ ���������
	element_particle** elements;
	bool* update_structure;

	unsigned int level_width = 0;
	unsigned int level_height = 0;
	float elements_size = 1.0f;

	// �����������
	game_level() = default;

	// �������� ������
	void load(unsigned int level_width, unsigned int level_height);

	// ������������� ��������� (� ��������������� �������� ������ ��� ������������� � ������ ������� ����)
	void elements_init(int n);

	// ��� ��� ������ ���������
	void update_element_sim();

	// ������ ������
	void draw(sprite_renderer* renderer) const;

	void clear();

	// ��������� ������� ��������
	uint32_t compute_idx(uint32_t x, uint32_t y) const;

	// ��������� �������� �� ��������� ��������:
	//element* get_element_at(uint32_t x, uint32_t y) const;
	element_particle* get_element_at(uint32_t x, uint32_t y) const;

	// ��������� ������� element �� ���������� � � �
	//void put_element(uint32_t x, uint32_t y, element* element);
	void put_element(
		uint32_t x, 
		uint32_t y, 
		element_particle* element
	) const;

	bool is_element_updated(uint8_t x, uint8_t y) const;

	// �������� �� �������������� ������� �����������
	bool is_element_in_bounds(uint32_t x, uint32_t y) const;

	// �������� �� ������� ������
	bool is_empty(uint32_t x, uint32_t y) const;

	// �������� �� ��, ��� � ������ ��������� ����
	bool is_water(uint32_t x, uint32_t y) const;

	// �������� �� ��, ��������� �� ������� �������
	bool is_element_completely_surrounded(uint32_t x, uint32_t y) const;

	void update_sand(uint32_t xpos, uint32_t ypos) const;

	void update_water(uint32_t xpos, uint32_t ypos) const;

	// ����� ��� ��������� �������� �� ������������ �����
	void draw_circle(
		int xc,
		int yc,
		int x,
		int y,
		element_particle* element
	) const;

	// ����� ���������� ���������� �� ������ ����������
	void circle_bres(
		int xc,
		int yc,
		int r,
		element_particle* element
	) const;

	// ��������� ��������� �����
	static int int_rand(const int& min, const int& max) {
		static thread_local std::mt19937 generator;
		const std::uniform_int_distribution<int> distribution(min, max);
		return distribution(generator);
	}
};
#endif