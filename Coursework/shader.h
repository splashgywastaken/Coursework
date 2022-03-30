#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// General purpose shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.

class shader
{
public:
    // state
    unsigned int id{};
    // constructor
    shader() = default;
    // sets the current shader as active
    shader& use();
    // compiles the shader from given source code
    void    compile( // note: geometry source code is optional 
        const char* vertex_source,
        const char* fragment_source, 
        const char* geometry_source = nullptr
    ); 
    // utility functions
    void    set_float(
        const char* name,
        float value, bool
        use_shader = false
    );
    void    set_integer(
        const char* name,
        int value, 
        bool use_shader = false
    );
    void    set_vector2_f(
        const char* name,
        float x,
        float y,
        bool use_shader = false
    );
    void    set_vector2_f(
        const char* name,
        const glm::vec2& value,
        bool use_shader = false
    );
    void    set_vector3_f(
        const char* name,
        float x, 
        float y,
        float z,
        bool use_shader = false
    );
    void    set_vector3_f(
        const char* name,
        const glm::vec3& value, 
        bool use_shader = false
    );
    void    set_vector4_f(
        const char* name, 
        float x,
        float y,
        float z, 
        float w, 
        bool use_shader = false
    );
    void    set_vector4_f(
        const char* name, 
        const glm::vec4& value, 
        bool use_shader = false
    );
    void    set_matrix4(
        const char* name,
        const glm::mat4& matrix,
        bool use_shader = false
    );
private:
    // checks if compilation or linking failed and if so, print the error logs
    static void    check_compile_errors(unsigned int object, std::string type);
};

#endif