#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

class sprite_renderer
{
public:
	explicit sprite_renderer(shader shader);
    ~sprite_renderer();

    // Используется для отрисовки клетки сетки
    void draw_sprite(
	    glm::vec2 position,
	    glm::vec2 size = glm::vec2(10.0f, 10.0f),
	    glm::vec3 color = glm::vec3(1.0f)
    );
private:
    // Переменные для отрисовки
    // Шейдер с помощью которого происходит отрисовка
    shader       shader_;
    // Массив объектов вершин
    unsigned int quad_vao_;

    // Метод - инициализатор данных для отрисовки
    void init_render_data();
};

#endif