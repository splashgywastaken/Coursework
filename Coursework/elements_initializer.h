#ifndef ELEMENTS_INITIALIZER_H
#define ELEMENTS_INITIALIZER_H
#include <random>

#include "element_particle.h"
#include "resource_manager.h"

/*
 * »нициализатор элементов дл€ создани€ новых на сетке
 * ќпределение значений переменных:
 *		“ипы элементов:
 *		0 - недвижимые объекты
 *		1 - двигающиес€ объекты
 *		2 - жидкости
 *		3 - газы (все что легче воздуха и при симул€ции поднимаетс€ вверх)
 *		»дентификаторы (id):
 *			0 - пустота,
 *			1 - песок,
 *			2 - вода
 *			3 - камень
 *			4 - соль
 *			5 - огонь
 *			6 - дерево
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

	static element_particle salt()
	{
		const float r = static_cast<float>(get_random_int(90, 100)) / (100.f * 255.f);

		return {
			1,
			4,
			glm::vec3(252 * r, 225 * r, 245 * r)
		};
	}

	static element_particle fire()
	{
		const float r = static_cast<float>(get_random_int(60, 90)) / (100.f * 255.f);
		
		return {
			3,
			5,
			glm::vec3(247 * r, 30 * r, 53 * r)
		};
	}

	static element_particle wood()
	{
		const float r = static_cast<float>(get_random_int(60, 80)) / (100.f * 255.f);
		
		return {
			0,
			6,
			glm::vec3(94 * r, 65 * r, 47 * r)
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