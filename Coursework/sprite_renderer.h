#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "texture_2d.h"

class sprite_renderer
{
public:
	explicit sprite_renderer(shader shader);
    ~sprite_renderer();

    void draw_sprite(
        const texture_2d& texture,
        glm::vec2 position,
        glm::vec2 size = glm::vec2(10.0f, 10.0f),
        float rotate = 0.0f,
        glm::vec3 color = glm::vec3(1.0f)
    );
private:
    shader       shader_;
    unsigned int quad_vao_;

    void init_render_data();
};

#endif