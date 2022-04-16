#ifndef ELEMENT_PARTICLE_H
#define ELEMENT_PARTICLE_H

#include <ostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "resource_manager.h"

/**
 *  ласс - плейсхолдер дл€ данных,
 * значени€ дл€ которого будет задавать инициализатор частиц
 */
class element_particle
{
public:
	int* type;
	int* id;
	glm::vec2* velocity;
	glm::vec3* color;
	bool* was_update_this_tick;

	element_particle() :
		type(nullptr),
		id(nullptr),
		velocity(nullptr),
		color(nullptr),
		was_update_this_tick(nullptr)
	{
	}

	~element_particle()
	{
		delete type;
		delete id;
		delete velocity;
		delete color;
	}

	element_particle(
		const int& type,
		const int& id,
		const glm::vec2& velocity,
		const glm::vec3& color
	);
	element_particle(const element_particle& other) = default;

	element_particle(element_particle&& other) noexcept
		: type(other.type),
		  id(other.id),
		  velocity(other.velocity),
		  color(other.color),
		  was_update_this_tick(other.was_update_this_tick)
	{
	}

	element_particle& operator=(const element_particle& other)
	{
		if (this == &other)
			return *this;
		type = other.type;
		id = other.id;
		velocity = other.velocity;
		color = other.color;
		was_update_this_tick = other.was_update_this_tick;
		return *this;
	}

	element_particle& operator=(element_particle&& other) noexcept
	{
		if (this == &other)
			return *this;
		type = other.type;
		id = other.id;
		velocity = other.velocity;
		color = other.color;
		was_update_this_tick = other.was_update_this_tick;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const element_particle& obj)
	{
		return os
			<< "type: " << obj.type
			<< " id: " << obj.id
			<< " velocity: " << obj.velocity
			<< " color: " << obj.color
			<< " was updated this frame: " << obj.color;
	}
};

inline element_particle::element_particle(
	const int& type,
	const int& id,
	const glm::vec2& velocity,
	const glm::vec3& color
) :
	type(new int(type)),
	id(new int(id)),
	velocity(new glm::vec2(velocity)),
	color(new glm::vec3(color)),
	was_update_this_tick(new bool(false))
{
}

#endif
