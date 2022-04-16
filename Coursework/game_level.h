#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <random>

#include "element_particle.h"
#include "sprite_renderer.h"

class game_level
{
public:
	// вектор элементов
	element_particle** elements;
	bool* update_structure;

	unsigned int level_width = 0;
	unsigned int level_height = 0;
	float elements_size = 1.0f;

	// конструктор
	game_level() = default;

	// загрузка уровня
	void load(unsigned int level_width, unsigned int level_height);

	// Инициализация элементов (и предварительное очищение памяти для использования в случае очистки поля)
	void elements_init(int n);

	// шаг для обхода элементов
	void update_element_sim();

	// рендер уровня
	void draw(sprite_renderer* renderer) const;

	void clear();

	// Получение индекса элемента
	uint32_t compute_idx(uint32_t x, uint32_t y) const;

	// Получение элемента по следующим индексам:
	//element* get_element_at(uint32_t x, uint32_t y) const;
	element_particle* get_element_at(uint32_t x, uint32_t y) const;

	// Поставить элемент element на координаты х и у
	//void put_element(uint32_t x, uint32_t y, element* element);
	void put_element(
		uint32_t x, 
		uint32_t y, 
		element_particle* element
	) const;

	bool is_element_updated(uint8_t x, uint8_t y) const;

	// Проверка на принадлежность игровым координатам
	bool is_element_in_bounds(uint32_t x, uint32_t y) const;

	// Проверка на пустоту ячейки
	bool is_empty(uint32_t x, uint32_t y) const;

	// Проверка на то, что в ячейке находится вода
	bool is_water(uint32_t x, uint32_t y) const;

	// Проверка на то, полностью ли элемент окружен
	bool is_element_completely_surrounded(uint32_t x, uint32_t y) const;

	void update_sand(uint32_t xpos, uint32_t ypos) const;

	void update_water(uint32_t xpos, uint32_t ypos) const;

	// Метод для установки пикселей на определенные точки
	void draw_circle(
		int xc,
		int yc,
		int x,
		int y,
		element_particle* element
	) const;

	// Метод построения окружности по методу Брезенхама
	void circle_bres(
		int xc,
		int yc,
		int r,
		element_particle* element
	) const;

	// Генератор случайных чисел
	static int int_rand(const int& min, const int& max) {
		static thread_local std::mt19937 generator;
		const std::uniform_int_distribution<int> distribution(min, max);
		return distribution(generator);
	}
};
#endif