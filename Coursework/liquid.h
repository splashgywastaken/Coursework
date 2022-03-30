#ifndef LIQUID_H
#define LIQUID_H

#include "element.h"

/**
 * Абстрактный класс "жидких" частиц.
 * Используется для определения типа частицы
 */
class liquid :
    public element
{
public:
	liquid() = default;
	liquid(
		const glm::vec2& pos,
		const glm::vec2& size,
		const texture_2d& sprite,
		const glm::vec3& color,
		const glm::vec2& velocity
	)
		: element(pos, size, sprite, color, velocity)
	{
	}
};

#endif