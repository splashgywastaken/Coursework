#ifndef ELEMENTS_INITIALIZER_H
#define ELEMENTS_INITIALIZER_H
#include <random>

#include "element_particle.h"
#include "resource_manager.h"

/*
 * Инициализатор элементов для создания новых на сетке
 * Определение значений переменных:
 *		Типы элементов:
 *		0 - недвижимые объекты
 *		1 - двигающиеся объекты
 *		2 - жидкости
 *		Идентификаторы (id):
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
		const float random_float = static_cast<float>(get_random_int()) / (100.f * 255.f);

		return {
			1,
			1,
			glm::vec3(216.0f * random_float, 169.0f * random_float, 64 / 255.0f)
		};
	}

	static element_particle water()
	{
		const float random_float = static_cast<float>(get_random_int()) / (100.f * 255.f);
		
		return {
			2,
			2,
			glm::vec3(54.0f * random_float, 26.0f * random_float, 192 * random_float)
		};
	}

	static element_particle stone()
	{
		const float random_float = static_cast<float>(get_random_int(0, 100)) / (100.f * 255.f);

		return {
			0,
			3,
			glm::vec3(125 * random_float, 125 * random_float, 125 * random_float)
		};
	}

	static element_particle salt()
	{
		const float random_float = static_cast<float>(get_random_int(90, 100)) / (100.f * 255.f);

		return {
			1,
			4,
			glm::vec3(252 * random_float, 225 * random_float, 245 * random_float)
		};
	}

	static element_particle fire()
	{
		const float random_float = static_cast<float>(get_random_int(60, 90)) / (100.f * 255.f);
		
		return {
			3,
			5,
			glm::vec3(247 * random_float, 30 * random_float, 53 * random_float)
		};
	}

	static element_particle wood()
	{
		const float random_float = static_cast<float>(get_random_int(60, 80)) / (100.f * 255.f);
		
		return {
			0,
			6,
			glm::vec3(94 * random_float, 65 * random_float, 47 * random_float)
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