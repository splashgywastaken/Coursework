#ifndef ELEMENTS_INITIALIZER_H
#define ELEMENTS_INITIALIZER_H
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
		const float r = get_random_float(32, 64);

		return {
			1,
			1,
			velocity,
			glm::vec3(216.0f / 255.0f, 169.0f / 255.0f, r / 255.0f)
		};
	}

	static element_particle water(glm::vec2 velocity)
	{
		const float r = get_random_float(214, 255);

		return {
			2,
			2,
			velocity,
			glm::vec3(54 / 255.0f, 26 / 255.0f, r / 255.0f)
		};
	}

private:
	static float get_random_float(const float min, const float max)
	{
		return min + static_cast <float> (rand()) / (RAND_MAX / (max - min));
	}

};
#endif