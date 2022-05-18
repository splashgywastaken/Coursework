#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include "shader.h"

// ����������� �������� �����, ������� �������� � ���� ���������
// ������� ��� �������� ��������. ������ ����������� ������
// ��� �� �������� � ������� �� ���� � ���� ������
// ��� ������ � ������� �����������, ���������� ������������
// �� ����������
class resource_manager
{
public:
    // ��������� ��������
    static std::map<std::string, shader>    shaders;
    // ��������� � ���������� ��������� ���������
    // �� .glsl ����� � ���������, ���������� �
    // (���� ����� ������) �������������� ��������
    static shader    load_shader(
				        const char* v_shader_file,
				        const char* f_shader_file,
				        const char* g_shader_file,
				        const std::string& name
					);
    // ���������� �������� ������
    static shader    get_shader(const std::string& name);
    // ��������� ����������� ������ �� ������������ ��������
    static void      clear();
private:
    // private �����������
    resource_manager() = default;
    // ��������� � ���������� ������ �� �����
    static shader    load_shader_from_file(
        const char* v_shader_file,
        const char* f_shader_file,
        const char* g_shader_file = nullptr
    );
};

#endif