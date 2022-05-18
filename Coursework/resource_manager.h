#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include "shader.h"

// Статический синглтон класс, который содержит в себе несколько
// методов для загрузки шейдеров. Каждый загруженный шейдер
// так же хранится с ссылкой на него в виде строки
// Все методы и ресурсы статические, публичного конструктора
// не определено
class resource_manager
{
public:
    // хранилище ресурсов
    static std::map<std::string, shader>    shaders;
    // загружает и генерирует шейдерную программу
    // из .glsl файла с вершинным, фрагментым и
    // (если такой указан) геометрическим шейдером
    static shader    load_shader(
				        const char* v_shader_file,
				        const char* f_shader_file,
				        const char* g_shader_file,
				        const std::string& name
					);
    // возвращает хранимый шейдер
    static shader    get_shader(const std::string& name);
    // правильно освобождает память от подгруженных ресурсов
    static void      clear();
private:
    // private конструктор
    resource_manager() = default;
    // загружает и генерирует шейдер из файла
    static shader    load_shader_from_file(
        const char* v_shader_file,
        const char* f_shader_file,
        const char* g_shader_file = nullptr
    );
};

#endif