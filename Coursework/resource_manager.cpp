#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <stb_image.h>

// Instantiate static variables
std::map<std::string, texture_2d>    resource_manager::textures;
std::map<std::string, shader>       resource_manager::shaders;


shader resource_manager::load_shader(
    const char* v_shader_file,
    const char* f_shader_file,
    const char* g_shader_file,
    const std::string& name
)
{
    shaders[name] = load_shader_from_file(v_shader_file, f_shader_file, g_shader_file);
    return shaders[name];
}

shader resource_manager::get_shader(const std::string& name)
{
    return shaders[name];
}

texture_2d resource_manager::load_texture(
    const char* file, 
    const bool alpha, 
    const std::string& name
)
{
    textures[name] = load_texture_from_file(file, alpha);
    return textures[name];
}

texture_2d resource_manager::get_texture(const std::string& name)
{
    return textures[name];
}

void resource_manager::clear()
{
    // (properly) delete all shaders	
    for (const auto& it : shaders)
        glDeleteProgram(it.second.id);
    // (properly) delete all textures
    for (const auto& it : textures)
        glDeleteTextures(1, &it.second.id);
}

shader resource_manager::load_shader_from_file(
    const char* v_shader_file,
    const char* f_shader_file,
    const char* g_shader_file
)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertex_code;
    std::string fragment_code;
    std::string geometry_code;
    try
    {
        // open files
        std::ifstream vertex_shader_file(v_shader_file);
        std::ifstream fragment_shader_file(f_shader_file);
        std::stringstream v_shader_stream, f_shader_stream;
        // read file's buffer contents into streams
        v_shader_stream << vertex_shader_file.rdbuf();
        f_shader_stream << fragment_shader_file.rdbuf();
        // close file handlers
        vertex_shader_file.close();
        fragment_shader_file.close();
        // convert stream into string
        vertex_code = v_shader_stream.str();
        fragment_code = f_shader_stream.str();
        // if geometry shader path is present, also load a geometry shader
        if (g_shader_file != nullptr)
        {
            std::ifstream geometry_shader_file(g_shader_file);
            std::stringstream g_shader_stream;
            g_shader_stream << geometry_shader_file.rdbuf();
            geometry_shader_file.close();
            geometry_code = g_shader_stream.str();
        }
    }
    catch (std::exception& e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* v_shader_code = vertex_code.c_str();
    const char* f_shader_code = fragment_code.c_str();
    const char* g_shader_code = geometry_code.c_str();
    // 2. now create shader object from source code
    shader shader;
    shader.compile(
        v_shader_code,
        f_shader_code,
        g_shader_file != nullptr ? g_shader_code : nullptr
    );
    return shader;
}

texture_2d resource_manager::load_texture_from_file(const char* file, const bool alpha)
{
    // create texture object
    texture_2d texture;
    if (alpha)
    {
        texture.internal_format = GL_RGBA;
        texture.image_format = GL_RGBA;
    }
    // load image
    int width, height, nr_channels;
    unsigned char* data = 
        stbi_load(
            file,
            &width,
            &height,
            &nr_channels,
            0
        );
    // now generate texture
    texture.generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}