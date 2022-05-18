#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <random>
#include "element_particle.h"
#include "sprite_renderer.h"

class elements_level
{
	// вектор элементов
	std::vector<element_particle*>* elements_{};
	bool* update_structure_{};
	// размер сетки
	int level_width_ = 0;
	int level_height_ = 0;

	// Метод для установки пикселей на определенные точки
	void draw_circle(
		const int& xc,
		const int& yc,
		const int& x,
		const int& y,
		const int& element_id
	) const;
	
	// Получение элемента по следующим индексам:
	element_particle* get_element_at(const int& x, const int& y) const;

	// удаление элемента на координатах x y
	void delete_element_at(const int& x, const int& y) const;

	// Поставить элемент element на координаты х и у
	void put_element(
		const int& x,
		const int& y,
		const int& element_id
	) const;

	//обновлялся ли элемент по координатам x y
	bool is_element_updated(const int& x, const int& y) const;

	// Проверка на принадлежность к определенному типу по координатам x y
	bool is_element_in_bounds(const int& x, const int& y) const;
	// Проверка на принадлежность к определенному типу по координатам x y
	// Если недвижимый
	bool is_solid(const int& x, const int& y) const;
	// Если газ
	bool is_gas(const int& x, const int& y) const;
	// Проверка на пустоту ячейки
	bool is_empty(const int& x, const int& y) const;
	// Проверка на то, что в ячейке находится вода
	bool is_water(const int& x, const int& y) const;
	// Проверка на то, что в ячейке находится огонь
	bool is_fire(const int& x, const int& y) const;

	// Проверка окружения элементов
	// Проверка на то, полностью ли элемент окружен
	bool is_completely_surrounded(int x, int y) const;
	// Проверка на то, что полностью окружен недвижымыми элементами
	bool is_completely_surrounded_by_solid(int x, int y) const;
	// Если находится рядом с водой
	bool is_near_water(int x, int y) const;
	// Если находится рядом с огнем
	bool is_near_fire(int x, int y) const;

	// Методы обновления клеток
	// песок
	bool update_sand(int x_position, int y_position) const;
	// вода
	bool update_water(int x_position, int y_position) const;
	// камень
	bool update_stone(int x_position, int y_position) const;
	// соль
	bool update_salt(int x_position, int y_position) const;
	// огонь
	bool update_fire(int x_position, int y_position) const;
	// дерево
	bool update_wood(int x_position, int y_position) const;

public:

	// конструктор
	elements_level() = default;

	// загрузка уровня
	void load(int input_level_width, int input_level_height);

	// Инициализация элементов (и предварительное очищение памяти для использования в случае очистки поля)
	void elements_init();

	// Очистка данных 
	void clear() const;

	// шаг для обхода элементов
	void update_element_level(float dt) const;

	// рендер уровня
	void draw(sprite_renderer* renderer) const;

	// Получение индекса элемента
	int compute_idx(int x, int y) const;

	// Метод построения окружности из элементов по алгоритму Брезенхама
	void circle_bres(
		int xc,
		int yc,
		int r,
		int element_id
	) const;

	// Метод построения окружности из пикселей по алгоритму Брезенхама
	void circle_bres(
		int xc,
		int yc,
		int brush_radius,
		sprite_renderer *renderer
	) const;
	
	// Метод для установки пикселей на определенные точки
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

	// Генератор случайных чисел
	static int int_rand(const int& min, const int& max) {
		static thread_local std::mt19937 generator;
		const std::uniform_int_distribution<int> distribution(min, max);
		return distribution(generator);
	}
};
#endif