#ifndef GAME_H
#define GAME_H

#include "elements_level.h"
#include "sprite_renderer.h"
#include "text_renderer.h"

class element_sim
{
	// ����
public:
	bool *pressed_keys;
	bool* mouse_buttons;
private:
	//������ � ������ ������
	unsigned int width_, height_;
	std::string fps_ = "60";
	bool simulation_is_paused_ = false;
	bool show_fps_ = false;
	int brush_radius_ = 8;
	int brush_element_id_ = 1;
	//�������� �������� ��� ��������:
	sprite_renderer *renderer_;
	//�������� �������
	text_renderer* text_;
	//������ - ������� �������
	elements_level *level_;

	// ������ � ������������
public:
	element_sim(
		unsigned width,
		unsigned height
	);
	~element_sim();

	// ������������� ���� ����������
	void init();
	// ������ ��� �������� �����
	void process_input(int x_position, int y_position);
	void update(float dt);
	void render(glm::vec2 mouse_position) const;

	// ������ ��� ��������� �������� ����������
	void change_brush_size(int delta);
	void set_fps(int fps);
	
private:
	// ����� ��� ������� �����
	void clear_level() const;
	// ������ ��� ������ � �������� �����������
	void change_pause_value();
	void change_show_fps_value();
	// ����� ��� ��������� ����� �� �����
	void draw_circle(
		uint32_t cx,
		uint32_t cy
	) const;
	// ������ ��� ��������� ����������������� �����
	void process_keyboard_input();
	void process_mouse_input(
		int x_position,
		int y_position
	);
};
#endif