#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Шейдерный объект общего назначения. Компилируется из файла,
// генерирует compile/link-time сообщения об ошибках и содержит
// в себе методы - утилиты для простого обращения с шейдером
class shader
{
public:
    // Состояние
    unsigned int id{};
    // конструктор
    shader() = default;
    // переводит данный шейдер в активное состояние
    shader& use();
    // компилирует шейдер из заданного исходного кода
    void    compile( // заметка: исходный код для геометрии - необязателен
        const char* vertex_source,
        const char* fragment_source
    ); 
    // методы - утилиты для задания значений переменным шейдера
    void    set_integer(
        const char* name,
        int value, 
        bool use_shader = false
    );
    void    set_vector3_f(
        const char* name,
        const glm::vec3& value, 
        bool use_shader = false
    );
    void    set_matrix4(
        const char* name,
        const glm::mat4& matrix,
        bool use_shader = false
    );
private:
    // проверка на ошибки при связывании или компиляции, если была ошибка, то вывести о ней данные
    static void    check_compile_errors(unsigned int object, std::string type);
};

#endif