#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>
#include <glm/glm.hpp>
#include "shader.h"

/// ������ � ���� ���������� ����������� � �������, ������������ � ������� FreeType
struct character {
    unsigned int texture_id; // ID - ���� ��� �����
    glm::ivec2   size;       // ������ �����
    glm::ivec2   bearing;    // ������ �� ��������� ������ � ����� ������� �����
    unsigned int advance;    // �������������� ������ ��� �����
};


// ����� - �������� ��� ��������� ������ ������������ �����, ������������
// FreeType �����������. 
class text_renderer
{
public:
    // ������ ������ �������������� ������������ ��������
    std::map<char, character> characters;
    // ������ ������������ ��� ��������� ������
    shader text_shader;
    // �����������
    text_renderer(unsigned int width, unsigned int height);
    // ������������ ������ �������� �� ��������� ������
    void load(const std::string& font, unsigned int font_size);
    // ������������ ������ ������, ��������� ������������� ������������ ������� ������
    void render_text(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
private:
    // ���������� ��� �������
    unsigned int vao_, vbo_;
};

#endif 