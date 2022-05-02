#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture_2d.h"
#include "shader.h"

/// Holds all state information relevant to a character as loaded using FreeType
struct character {
    unsigned int texture_id; // ID handle of the glyph texture
    glm::ivec2   size;       // size of glyph
    glm::ivec2   bearing;    // offset from baseline to left/top of glyph
    unsigned int advance;    // horizontal offset to advance to next glyph
};


// A renderer class for rendering text displayed by a font loaded using the 
// FreeType library. A single font is loaded, processed into a list of Character
// items for later rendering.
class text_renderer
{
public:
    // holds a list of pre-compiled Characters
    std::map<char, character> characters;
    // shader used for text rendering
    shader text_shader;
    // constructor
    text_renderer(unsigned int width, unsigned int height);
    // pre-compiles a list of characters from the given font
    void load(const std::string& font, unsigned int font_size);
    // renders a string of text using the precompiled list of characters
    void render_text(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
private:
    // render state
    unsigned int vao_, vbo_;
};

#endif 