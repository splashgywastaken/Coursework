#include "element_sim.h"

#include "resource_manager.h"
#include "sprite_renderer.h"

element_sim::element_sim(
	const unsigned width,
	const unsigned height
)
	:
	state(game_state::game_menu),
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
    // set render-specific controls
    renderer = new sprite_renderer(resource_manager::get_shader("element"));
    //// load textures
    //resource_manager::load_texture( "../textures/element.png", false, "sand");
    //resource_manager::load_texture("../textures/empty.png", true, "empty");
    //resource_manager::load_texture("../textures/empty.png", true, "water");
}

void element_sim::update(float dt) const
{
    if (!pause_simulation)
	{
		level->update_element_sim();
	}
}

void element_sim::render() const
{
    level->draw(renderer);
}

void element_sim::clear_level() const
{
    level->clear();
}

void element_sim::pause()
{
    pause_simulation = !pause_simulation;
}

void element_sim::draw_circle(
	element_particle* element,
	const uint32_t cx,
	const uint32_t cy,
	uint32_t r
) const
{
	while (r > 0)
	{
		level->circle_bres(cx, cy, --r, element);
	}

}
