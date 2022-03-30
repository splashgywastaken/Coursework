#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class texture_2d
{
public:
    // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    unsigned int id = 0;
    // texture image dimensions
    GLsizei texture_width, texture_height; // texture_width and texture_height of loaded image in pixels
    // texture Format
    GLint internal_format; // format of texture object
    GLint image_format; // format of loaded image
    // texture configuration
    GLint wrap_s; // wrapping mode on S axis
    GLint wrap_t; // wrapping mode on T axis
    GLint filter_min; // filtering mode if texture pixels < screen pixels
    GLint filter_max; // filtering mode if texture pixels > screen pixels
    // constructor (sets default texture modes)
    texture_2d();
    // generates texture from image data
    void generate(
        GLsizei width,
        GLsizei height,
        const unsigned char* data
    );
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void bind() const;
};

#endif