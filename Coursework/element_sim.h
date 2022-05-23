#ifndef GAME_H
#define GAME_H

#include "elements_level.h"
#include "sprite_renderer.h"
#include "text_renderer.h"

class element_sim
{
	// Поля
public:
	bool *pressed_keys;
	bool* mouse_buttons;
private:
	//Ширина и высота экрана
	unsigned int width_, height_;
	std::string fps_ = "60";
	bool simulation_is_paused_ = false;
	bool show_fps_ = false;
	int brush_radius_ = 8;
	int brush_element_id_ = 1;
	//Рендерер спрайтов для объектов:
	sprite_renderer *renderer_;
	//Рендерер шрифтов
	text_renderer* text_;
	//Объект - игровой уровень
	elements_level *level_;

	// Методы и конструкторы
public:
	element_sim(
		unsigned width,
		unsigned height
	);
	~element_sim();

	// Инициализация всех переменных
	void init();
	// Методы для игрового цикла
	void process_input(int x_position, int y_position);
	void update(float dt);
	void render(glm::vec2 mouse_position) const;

	// Методы для изменения значений переменных
	void change_brush_size(int delta);
	void set_fps(int fps);
	
private:
	// Метод для очистки сетки
	void clear_level() const;
	// Методы для работы с булевыми переменными
	void change_pause_value();
	void change_show_fps_value();
	// Метод для отрисовки круга на сетке
	void draw_circle(
		uint32_t cx,
		uint32_t cy
	) const;
	// Методы для обработки пользовательского ввода
	void process_keyboard_input();
	void process_mouse_input(
		int x_position,
		int y_position
	);
};
#endif