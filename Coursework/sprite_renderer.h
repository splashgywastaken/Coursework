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

    // ������������ ��� ��������� ������ �����
    void draw_sprite(
	    glm::vec2 position,
	    glm::vec2 size = glm::vec2(10.0f, 10.0f),
	    glm::vec3 color = glm::vec3(1.0f)
    );
private:
    // ���������� ��� ���������
    // ������ � ������� �������� ���������� ���������
    shader       shader_;
    // ������ �������� ������
    unsigned int quad_vao_;

    // ����� - ������������� ������ ��� ���������
    void init_render_data();
};

#endif