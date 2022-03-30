#include "shader.h"

#include <iostream>

shader& shader::use()
{
    glUseProgram(this->id);
    return *this;
}

void shader::compile(
    const char* vertex_source,
    const char* fragment_source,
    const char* geometry_source
)
{
    unsigned int g_shader;
    // vertex Shader
    const unsigned int s_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s_vertex, 1, &vertex_source, nullptr);
    glCompileShader(s_vertex);
    check_compile_errors(s_vertex, "VERTEX");
    // fragment Shader
    const unsigned int s_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s_fragment, 1, &fragment_source, nullptr);
    glCompileShader(s_fragment);
    check_compile_errors(s_fragment, "FRAGMENT");
    // if geometry shader source code is given, also compile geometry shader
    if (geometry_source != nullptr)
    {
        g_shader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(g_shader, 1, &geometry_source, NULL);
        glCompileShader(g_shader);
        check_compile_errors(g_shader, "GEOMETRY");
    }
    // shader program
    this->id = glCreateProgram();
    glAttachShader(this->id, s_vertex);
    glAttachShader(this->id, s_fragment);
    if (geometry_source != nullptr)
        glAttachShader(this->id, g_shader);
    glLinkProgram(this->id);
    check_compile_errors(this->id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(s_vertex);
    glDeleteShader(s_fragment);
    if (geometry_source != nullptr)
        glDeleteShader(g_shader);
}

void shader::set_float(
    const char* name,
    const float value,
    const bool use_shader
)
{
    if (use_shader)
        this->use();
    glUniform1f(glGetUniformLocation(this->id, name), value);
}
void shader::set_integer(
    const char* name,
    const int value,
    const bool use_shader
)
{
    if (use_shader)
        this->use();
    glUniform1i(glGetUniformLocation(this->id, name), value);
}
void shader::set_vector2_f(
    const char* name,
    const float x,
    const float y,
    const bool use_shader
)
{
    if (use_shader)
        this->use();
    glUniform2f(glGetUniformLocation(this->id, name), x, y);
}
void shader::set_vector2_f(
    const char* name,
    const glm::vec2& value,
    const bool use_shader
)
{
    if (use_shader)
        this->use();
    glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}
void shader::set_vector3_f(
    const char* name,
    const float x,
    const float y,
    const float z,
    const bool use_shader
)
{
    if (use_shader)
        this->use();
    glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
}
void shader::set_vector3_f(
    const char* name, 
    const glm::vec3& value,
    const bool use_shader
)
{
    if (use_shader)
        this->use();
    glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}
void shader::set_vector4_f(
    const char* name,
    const float x,
    const float y,
    const float z,
    const float w,
    const bool use_shader
)
{
    if (use_shader)
        this->use();
    glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}
void shader::set_vector4_f(
    const char* name,
    const glm::vec4& value,
    const bool use_shader
)
{
    if (use_shader)
        this->use();
    glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}
void shader::set_matrix4(
    const char* name,
    const glm::mat4& matrix,
    const bool use_shader
)
{
    if (use_shader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(matrix));
}


void shader::check_compile_errors(const unsigned int object, const std::string type)
{
    int success;
    char info_log[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, nullptr, info_log);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << info_log << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, info_log);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << info_log << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}