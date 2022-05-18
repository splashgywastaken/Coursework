#include "sprite_renderer.h"

#include "camera.h"

sprite_renderer::sprite_renderer(shader shader)
    :
    shader_(shader),
    quad_vao_(0)
{
    this->init_render_data();
}

sprite_renderer::~sprite_renderer()
{
    glDeleteVertexArrays(1, &this->quad_vao_);
}

void sprite_renderer::init_render_data()
{
    // configure VAO/VBO
    unsigned int vbo;
    constexpr float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quad_vao_);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quad_vao_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void*>(nullptr));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void sprite_renderer::draw_sprite(
    const glm::vec2 position,
    const glm::vec2 size,
	const glm::vec3 color
)
{
    this->shader_.use();
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shader_.set_matrix4("model", model);
    this->shader_.set_vector3_f("spriteColor", color);

    glBindVertexArray(this->quad_vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
