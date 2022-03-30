#ifndef SOLID_H
#define SOLID_H

#include "element.h"

/**
 * Ѕазовый абстрактный класс дл€ твердых частиц.
 * »спользуетс€ дл€ определени€ типа частицы
 */
class solid :
    public element
{
public:
	solid() = default;
	solid(
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