#ifndef IMMOVABLE_SOLID_H
#define IMMOVABLE_SOLID_H

#include "solid.h"

/**
 * Базовый абстрактный класс для твердых частиц, которые не могут двигаться.
 * Используется для определения поведения частиц.
 */
class immovable_solid :
    public solid
{
public:
	immovable_solid() = default;
	immovable_solid(
		const glm::vec2& pos,
		const glm::vec2& size,
		const texture_2d& sprite,
		const glm::vec3& color,
		const glm::vec2& velocity
	)
		: solid(pos, size, sprite, color, velocity)
	{
	}
};

#endif