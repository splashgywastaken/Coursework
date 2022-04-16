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
	static element_particle empty()
	{
		return {
			0,
			0,
			glm::vec2(0.0f),
			glm::vec3(0.0f)
		};
	}

	static element_particle sand(glm::vec2 velocity)
	{
		const float r = get_random_int(32, 64);

		return {
			1,
			1,
			velocity,
			glm::vec3(216.0f / 255.0f, 169.0f / 255.0f, r / 255.0f)
		};
	}

	static element_particle water(glm::vec2 velocity)
	{
		const float r = get_random_int(214, 255);

		return {
			2,
			2,
			velocity,
			glm::vec3(54 / 255.0f, 26 / 255.0f, r / 255.0f)
		};
	}

	static element_particle stone()
	{
		const float r = get_random_int(50, 125);
		return {
			0,
			3,
			glm::vec2(0.0f),
			glm::vec3(r/ 255.0f, r / 255.0f, r / 255.0f)
		};
	}

private:
	static float get_random_int(const float min, const float max)
	{
		static thread_local std::mt19937 generator;
		const std::uniform_int_distribution<int> distribution(min, max);
		return distribution(generator);
	}

};
#endif