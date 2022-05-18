#include "element_sim.h"

#include <iostream>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

element_sim::element_sim(
	const unsigned width,
	const unsigned height
)
	:
	width_(width),
	height_(height),
	renderer_(nullptr),
	level_(new elements_level())
{
    // допилить использование игрового уровня
    level_->load(width, height);
}

element_sim::~element_sim() = default;

void element_sim::init()
{
    // Загрузка шейдеров
    resource_manager::load_shader(
        "../shaders/basic_shader_vert.glsl",
        "../shaders/basic_shader_frag.glsl", 
        nullptr, 
        "element"
    );
    // Настройка шейдеров
    const glm::mat4 projection = glm::ortho(
        0.0f, 
        static_cast<float>(this->width_),
        static_cast<float>(this->height_),
        0.0f, 
        -1.0f, 
        1.0f
    );
    resource_manager::get_shader("element").use().set_integer("image", 0);
    resource_manager::get_shader("element").set_matrix4("projection", projection);
    // Задаём новый рендерер
    renderer_ = new sprite_renderer(resource_manager::get_shader("element"));

    // Подгрузка обработчика шрифтов:
    text_ = new text_renderer(this->width_, this->height_);
    text_->load("../Fonts/ArcadeClassic.TTF", 24);

    pressed_keys = new bool[1024]{};
    mouse_buttons = new bool[3] {};
}

void element_sim::process_input(const int x_position, const int y_position)
{
    process_mouse_input(x_position, y_position);
    process_keyboard_input();
}

void element_sim::update(const float dt)
{
    if (!simulation_is_paused_)
	{
		level_->update_element_level(dt);
	}
}

void element_sim::render(const glm::vec2 mouse_position) const
{
    level_->draw(renderer_);

    text_->render_text(
		"Sandbox", 5.0f, 5.0f, 1.f
    );
    if (simulation_is_paused_)
    {
        text_->render_text(
            "paused",
            100.0f, 6.5f,
            0.75f
        );
    }

    std::string current_element;
    glm::vec3 color;
    switch (brush_element_id_)
    {
    case 1:
        current_element = "sand";
        color = glm::vec3(216.0f / 255.0f, 169.0f / 255.0f, 64 / 255.0f);
        break;
    case 2:
        current_element = "water";
        color = glm::vec3(54 / 255.0f, 26 / 255.0f, 192 / 255.0f);
        break;
    case 3:
        current_element = "stone";
        color = glm::vec3(125 / 255.0f, 125 / 255.0f, 125 / 255.0f);
        break;
    case 4:
        current_element = "salt";
        color = glm::vec3(252 / 255.0f, 225 / 255.0f, 245 / 255.0f);
        break;
    case 5:
        current_element = "fire";

        color = glm::vec3(247 / 255.0f, 30/255.0f, 53 / 255.0f);
        break;
    case 6:
        current_element = "wood";
        color = glm::vec3(94 / 255.0f, 65 / 255.0f, 47 / 255.0f);
        break;
    default: 
        current_element = "none";
        color = glm::vec3(1.0f);
    }
    text_->render_text(
        "Using  element  " + current_element,
        5.0f, 25.0f, .75f,
        color
    );
    if (show_fps_)
	{
		text_->render_text(
		   "fps " + fps_,
		   5.0f, 45.0f, .75f
	   );
	}

    level_->circle_bres(mouse_position.x, mouse_position.y, brush_radius_, renderer_);

}

void element_sim::process_keyboard_input()
{
	if (pressed_keys[GLFW_KEY_P])
	{
		change_pause_value();
        pressed_keys[GLFW_KEY_P] = false;
	}
	else if (pressed_keys[GLFW_KEY_C])
    {
        clear_level();
        pressed_keys[GLFW_KEY_C] = false;
    }
    else if (pressed_keys[GLFW_KEY_F1])
    {
        change_show_fps_value();
        pressed_keys[GLFW_KEY_F1] = false;
    }
    else if (pressed_keys[GLFW_KEY_1])
    {
        brush_element_id_ = 1;
        pressed_keys[GLFW_KEY_1] = false;
    }
    else if (pressed_keys[GLFW_KEY_2])
    {
        brush_element_id_ = 2;
        pressed_keys[GLFW_KEY_2] = false;
    }
    else if (pressed_keys[GLFW_KEY_3])
    {
        brush_element_id_ = 3;
        pressed_keys[GLFW_KEY_3] = false;
    }
    else if (pressed_keys[GLFW_KEY_4])
    {
        brush_element_id_ = 4;
        pressed_keys[GLFW_KEY_4] = false;
    }
    else if (pressed_keys[GLFW_KEY_5])
    {
        brush_element_id_ = 5;
        pressed_keys[GLFW_KEY_5] = false;
    }
    else if (pressed_keys[GLFW_KEY_6])
    {
        brush_element_id_ = 6;
        pressed_keys[GLFW_KEY_6] = false;
    }
}

void element_sim::process_mouse_input(const int x_position, const int y_position)
{

    if (mouse_buttons[GLFW_MOUSE_BUTTON_1])
    {
        draw_circle(x_position, y_position);
    }
    else if (mouse_buttons[GLFW_MOUSE_BUTTON_2])
    {
	    const auto current_element_id = new int(brush_element_id_);
        brush_element_id_ = 0;
        draw_circle(x_position, y_position);
        brush_element_id_ = *current_element_id;
        delete current_element_id;
    }

}

void element_sim::change_brush_size(const int delta)
{
    if (brush_radius_ <= 64 && brush_radius_ > 1)
    {
        brush_radius_ += delta;
    }
}

void element_sim::set_fps(const int fps)
{
    fps_ = std::to_string(fps);
}

void element_sim::clear_level() const
{
    level_->clear();
    level_->elements_init();
}

void element_sim::change_pause_value()
{
    simulation_is_paused_ = !simulation_is_paused_;
}

void element_sim::change_show_fps_value()
{
    show_fps_ = !show_fps_;
}

void element_sim::draw_circle(
	const uint32_t cx,
	const uint32_t cy
) const
{
    int r = brush_radius_;
	while (r > 0)
	{
		level_->circle_bres(cx, cy, --r, brush_element_id_);
	}
}
