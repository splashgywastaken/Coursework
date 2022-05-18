#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// ��������� ������ ������ ����������. ������������� �� �����,
// ���������� compile/link-time ��������� �� ������� � ��������
// � ���� ������ - ������� ��� �������� ��������� � ��������
class shader
{
public:
    // ���������
    unsigned int id{};
    // �����������
    shader() = default;
    // ��������� ������ ������ � �������� ���������
    shader& use();
    // ����������� ������ �� ��������� ��������� ����
    void    compile( // �������: �������� ��� ��� ��������� - ������������
        const char* vertex_source,
        const char* fragment_source
    ); 
    // ������ - ������� ��� ������� �������� ���������� �������
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
    // �������� �� ������ ��� ���������� ��� ����������, ���� ���� ������, �� ������� � ��� ������
    static void    check_compile_errors(unsigned int object, std::string type);
};

#endif