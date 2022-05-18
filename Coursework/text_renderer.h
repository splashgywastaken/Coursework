#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>
#include <glm/glm.hpp>
#include "shader.h"

/// Хранит в себе информацию относящуюся к символу, загруженному с помощью FreeType
struct character {
    unsigned int texture_id; // ID - поле для глифа
    glm::ivec2   size;       // Размер глифа
    glm::ivec2   bearing;    // оффсет от основного уровня в левую верхнюю часть
    unsigned int advance;    // горизонтальный оффсет для глифа
};


// Класс - рендерер для отрисовки текста использующий шрифт, обработанный
// FreeType библиотекой. 
class text_renderer
{
public:
    // хранит список предварительно обработанных символов
    std::map<char, character> characters;
    // шейдер используемый для отрисовки текста
    shader text_shader;
    // конструктор
    text_renderer(unsigned int width, unsigned int height);
    // обрабатывает списко символов из заданного шрифта
    void load(const std::string& font, unsigned int font_size);
    // отрисовывает строку текста, используя предврательно обработанные символы шрифта
    void render_text(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
private:
    // переменные для рендера
    unsigned int vao_, vbo_;
};

#endif 