#ifndef GAS_H
#define GAS_H

#include "element.h"

/**
 * Базовый абстрактный класс для частиц типа "газ".
 * Используется для определения типа частиц.
 */
class gas :
    public element
{
public:
	gas() = default;
	gas(
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