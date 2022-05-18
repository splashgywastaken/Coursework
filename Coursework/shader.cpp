#include "shader.h"

#include <iostream>

shader& shader::use()
{
    glUseProgram(this->id);
    return *this;
}

void shader::compile(
    const char* vertex_source,
    const char* fragment_source
)
{
    // вершинный шейдер
    const unsigned int s_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s_vertex, 1, &vertex_source, nullptr);
    glCompileShader(s_vertex);
    check_compile_errors(s_vertex, "VERTEX");
    // фрагментный шейдер
    const unsigned int s_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s_fragment, 1, &fragment_source, nullptr);
    glCompileShader(s_fragment);
    check_compile_errors(s_fragment, "FRAGMENT");
    // шейдерная программа
    this->id = glCreateProgram();
    glAttachShader(this->id, s_vertex);
    glAttachShader(this->id, s_fragment);
    glLinkProgram(this->id);
    check_compile_errors(this->id, "PROGRAM");
    // удаление всех шейдеров т.к. они связанны с нашей программой и больше не нужны
    glDeleteShader(s_vertex);
    glDeleteShader(s_fragment);
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