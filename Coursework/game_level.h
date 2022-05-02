#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <random>

#include "element_particle.h"
#include "sprite_renderer.h"

class game_level
{
public:
	// ������ ���������
	std::vector<element_particle*>* elements{};
	bool* update_structure{};

	int level_width = 0;
	int level_height = 0;
	float elements_size = 1.0f;

	// �����������
	game_level() = default;

	// �������� ������
	void load(int input_level_width, int input_level_height);

	// ������������� ��������� (� ��������������� �������� ������ ��� ������������� � ������ ������� ����)
	void elements_init();

	// ������� ������ 
	void clear() const;

	// ��� ��� ������ ���������
	void update_element_sim(float dt) const;

	// ������ ������
	void draw(sprite_renderer* renderer) const;

	// ��������� ������� ��������
	int compute_idx(int x, int y) const;

	// ��������� �������� �� ��������� ��������:
	element_particle* get_element_at(const int& x, const int& y) const;

	// ��������� ������� element �� ���������� � � �
	void put_element(
		const short int& x,
		const short int& y,
		const short int& element_id
	) const;

	bool is_element_updated(const int& x, const int& y) const;

	// �������� �� �������������� ������� �����������
	bool is_element_in_bounds(const int& x, const int& y) const;

	// �������� �� ������� ������
	bool is_empty(const int& x, const int& y) const;

	// �������� �� ��, ��� � ������ ��������� ����
	bool is_water(const int& x, const int& y) const;

	// �������� �� ��, ��������� �� ������� �������
	bool is_element_completely_surrounded(int x, int y) const;

	//
	// ������ ���������� ������
	//
	bool update_sand(int x_position, int y_position) const;

	bool update_water(int x_position, int y_position) const;

	bool update_stone(int x_position, int y_position) const;

	bool update_salt(int x_position, int y_position);

	// ����� ��� ��������� �������� �� ������������ �����
	void draw_circle(
		const int& xc,
		const int& yc,
		const int& x,
		const int& y,
		const int& element_id
	) const;

	// ����� ���������� ���������� �� ������ ����������
	void circle_bres(
		int xc,
		int yc,
		int r,
		int element_id
	) const;

	// ����� ���������� ���������� �� ������ ����������
	void circle_bres(
		int xc,
		int yc,
		int brush_radius,
		sprite_renderer *renderer
	) const;
	
	// ����� ��� ��������� �������� �� ������������ �����
	static void draw_circle(
		int xc,
		int yc,
		int x,
		int y,
		sprite_renderer* renderer
	);

	static void put_pixel(
		int x, 
		int y,
		sprite_renderer* renderer
	);

	// ��������� ��������� �����
	static int int_rand(const int& min, const int& max) {
		static thread_local std::mt19937 generator;
		const std::uniform_int_distribution<int> distribution(min, max);
		return distribution(generator);
	}
};
#endif