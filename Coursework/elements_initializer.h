#ifndef ELEMENTS_INITIALIZER_H
#define ELEMENTS_INITIALIZER_H
#include <random>

#include "element_particle.h"
#include "resource_manager.h"

/**
 * ������������� ��������� ��� �������� ����� �� �����
 * ����������� �������� ����������:
 *		���� ���������:
 *			0 - ���������� �������
 *			1 - ����������� �������
 *			2 - ��������
 *			3 - ���� (��� ��� ����� ������� � ��� ��������� ����������� �����)
 *		�������������� (id):
 *			0 - �������,
 *			1 - �����,
 *			2 - ����
 *			3 - ������
 */
class elements_initializer
{

public:
	static element_particle sand()
	{
		const float r = static_cast<float>(get_random_int()) / (100.f * 255.f);

		return {
			1,
			1,
			glm::vec3(216.0f * r, 169.0f * r, 64 / 255.0f)
		};
	}

	static element_particle water()
	{
		const float r = static_cast<float>(get_random_int()) / (100.f * 255.f);
		
		return {
			2,
			2,
			glm::vec3(54.0f * r, 26.0f * r, 192 * r)
		};
	}

	static element_particle stone()
	{
		const float r = static_cast<float>(get_random_int(0, 100)) / (100.f * 255.f);

		return {
			0,
			3,
			glm::vec3(125 * r, 125 * r, 125 * r)
		};
	}

	static element_particle empty()
	{
		return {};
	}

private:
	static int get_random_int(const int min = 70, const int max = 100)
	{
		static thread_local std::mt19937 generator;
		const std::uniform_int_distribution<int> distribution(min, max);
		return distribution(generator);
	}

};
#endif