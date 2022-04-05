#ifndef SAND_H
#define SAND_H
#include "elements_data.h"
#include "movable_solid.h"

class sand :
public movable_solid
{
public:
	sand() = default;
	sand(
		glm::vec2& pos, 
		glm::vec2& size, 
		texture_2d& sprite,
		glm::vec2& velocity
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

	sand(
		glm::vec2 pos,
		glm::vec2 size,
		texture_2d sprite,
		glm::vec2 velocity
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
	void step(std::vector<std::vector<element*>> elements) override;
};

inline bool sand::receive_heat()
{

	return true;

}

inline void sand::step(std::vector<std::vector<element*>> elements)
{



}

#endif
