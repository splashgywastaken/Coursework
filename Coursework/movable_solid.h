#ifndef MOVABLE_SOLID_H
#define MOVABLE_SOLID_H

#include "solid.h"

/**
 * ������� ����������� ����� ��� ������� ������, ������� ����� ���������.
 * ������������ ��� ����������� ��������� ������.
 */
class movable_solid :
    public solid
{
public:
	movable_solid() = default;
	movable_solid(
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