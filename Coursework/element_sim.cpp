#include "element_sim.h"

#include "resource_manager.h"
#include "sprite_renderer.h"

element_sim::element_sim(
	const unsigned width,
	const unsigned height
)
	:
	width(width),
	height(height),
	renderer(nullptr),
	level(new game_level())
{
    // допилить использование игрового уровня
    level->load(width, height);
}

element_sim::~element_sim() = default;

void element_sim::init()
{
    // load shaders
    resource_manager::load_shader(
        "../shaders/basic_shader_vert.glsl",
        "../shaders/basic_shader_frag.glsl", 
        nullptr, 
        "element"
    );
    // configure shaders
    const glm::mat4 projection = glm::ortho(
        0.0f, 
        static_cast<float>(this->width),
        static_cast<float>(this->height),
        0.0f, 
        -1.0f, 
        1.0f
    );
    resource_manager::get_shader("element").use().set_integer("image", 0);
    resource_manager::get_shader("element").set_matrix4("projection", projection);
    // Задаём новый рендерер
    renderer = new sprite_renderer(resource_manager::get_shader("element"));

    // Подгрузка обработчика шрифтов:
    text = new text_renderer(this->width, this->height);
    text->load("../Fonts/ArcadeClassic.TTF", 24);
}

// TODO: Сделать вывод фпс, добавить кнопки для выбора элементов

void element_sim::update(const float dt)
{
    this->dt = dt;

    if (!pause_simulation)
	{
		level->update_element_sim(dt);
	}
}

void element_sim::render(const int element_id, const int brush_radius, const glm::vec2 mouse_position) const
{
    level->draw(renderer);

    text->render_text(
		"Sandbox", 5.0f, 5.0f, 1.f
    );
    if (pause_simulation)
    {
        text->render_text(
            "paused",
            100.0f, 6.5f,
            0.75f
        );
    }

    std::string current_element;
    glm::vec3 color;
    switch (element_id)
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
    default: 
        current_element = "none";
        color = glm::vec3(1.0f);
    }
    text->render_text(
        "Using  element  " + current_element,
        5.0f, 25.0f, .75f,
        color
    );



    level->circle_bres(mouse_position.x, mouse_position.y, brush_radius, renderer);

}

void element_sim::clear_level() const
{
    level->clear();
    level->elements_init();
}

void element_sim::pause()
{
    pause_simulation = !pause_simulation;
}

void element_sim::draw_circle(
	const int element_id,
	const uint32_t cx,
	const uint32_t cy,
	uint32_t r
) const
{
	while (r > 0)
	{
		level->circle_bres(cx, cy, --r, element_id);
	}
}
