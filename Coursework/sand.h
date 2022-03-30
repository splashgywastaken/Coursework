#ifndef SAND_H
#define SAND_H
#include "elements_data.h"
#include "movable_solid.h"

class sand : movable_solid
{
public:
	sand() = default;

	sand(
		const glm::vec2& pos, 
		const glm::vec2& size, 
		const texture_2d& sprite,
		const glm::vec2& velocity
	)
		: movable_solid(
			pos, 
			size, 
			sprite,
			// Приблизительно темно-желтый цвет 
			color = glm::vec3(216.0f / 255.0f, 169.0f / 255.0f, 12.0f / 255.0f),
			velocity
		)
	{
		id = ELEMENT_SAND;
	}

	bool receive_heat() override;
};

inline bool sand::receive_heat()
{



}

#endif
