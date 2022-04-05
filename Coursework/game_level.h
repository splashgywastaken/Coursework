#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H
#include <vector>

#include "element.h"

class game_level
{
public:
	// матрица элементов
	std::vector<element*> elements;
	unsigned int level_width = 0;
	unsigned int level_height = 0;

	// конструктор
	game_level() = default;

	// загрузка уровня
	void load(unsigned int level_width, unsigned int level_height);

	// шаг для обхода элементов
	void simulate();

	// рендер уровня
	void draw(sprite_renderer* renderer) const;

	// Получение индекса элемента
	uint32_t compute_idx(uint32_t x, uint32_t y) const;

	// Получение элемента по следующим индексам:
	element* get_element_at(uint32_t x, uint32_t y) const;

	// Проверка на принадлежность игровым координатам
	bool is_element_in_bounds(uint32_t x, uint32_t y) const;

	// Проверка на пустоту ячейки
	bool is_empty(uint32_t x, uint32_t y) const;

	// Проверка на то, полностью ли элемент окружен
	bool is_element_completely_surrounded(uint32_t x, uint32_t y) const;

	// Поставить элемент element на координаты х и у
	void put_element(uint32_t x, uint32_t y, element* element);

	// Метод для установки пикселей на определенные точки
	void draw_circle(
		const int xc,
		const int yc,
		const int x,
		const int y,
		element* element
	);

	// Метод построения окружности по методу Брезенхама
	void circle_bres(
		const int xc,
		const int yc,
		const int r,
		element* element
	);

	void update_sand(uint32_t xpos, uint32_t ypos);

	//TODO: Добавить методы по обновлению состояний элементов в сетке
};
#endif