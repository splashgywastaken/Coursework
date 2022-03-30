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
	height(height), renderer(nullptr)
{
}

element_sim::~element_sim() = default;

void element_sim::init()
{
    // load shaders
    resource_manager::load_shader(
        "../shaders/basic_shader_vert.glsl",
        "../shaders/basic_shader_frag.glsl", 
        nullptr, 
        "sprite"
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
    resource_manager::get_shader("sprite").use().set_integer("image", 0);
    resource_manager::get_shader("sprite").set_matrix4("projection", projection);
    // set render-specific controls
    renderer = new sprite_renderer(resource_manager::get_shader("sprite"));
    // load textures
    resource_manager::load_texture( "../textures/awesomeface.png", true, "face");
}

void element_sim::update(float dt)
{
	
}

void element_sim::process_input(float dt)
{

}

void element_sim::render()
{
    renderer->draw_sprite(
        resource_manager::get_texture("face"),
        glm::vec2(200.0f, 200.0f), 
        glm::vec2(300.0f, 400.0f),
        45.0f,
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
}