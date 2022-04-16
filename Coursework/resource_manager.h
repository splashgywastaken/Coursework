#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "shader.h"
#include "texture_2d.h"


// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
class resource_manager
{
public:
    // resource storage
    static std::map<std::string, shader>    shaders;
    static std::map<std::string, texture_2d> textures;
    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static shader    load_shader(
				        const char* v_shader_file,
				        const char* f_shader_file,
				        const char* g_shader_file,
				        const std::string& name
					);
    // retrieves a stored shader
    static shader    get_shader(const std::string& name);
    // loads (and generates) a texture from file
    static texture_2d load_texture(
        const char* file,
        bool alpha,
        const std::string& name
    );
    // retrieves a stored texture
    static texture_2d get_texture(const std::string& name);
    // properly de-allocates all loaded resources
    static void      clear();
private:
    // private constructor, that is we do not want any actual resource manager objects.
    // Its members and functions should be publicly available (static).
    resource_manager() = default;
    // loads and generates a shader from file
    static shader    load_shader_from_file(
        const char* v_shader_file,
        const char* f_shader_file,
        const char* g_shader_file = nullptr
    );
    // loads a single texture from file
    static texture_2d load_texture_from_file(const char* file, bool alpha);
};

#endif