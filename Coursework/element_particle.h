#ifndef ELEMENT_PARTICLE_H
#define ELEMENT_PARTICLE_H

#include <ostream>
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
	glm::vec3* color;

	element_particle() :
		type(nullptr),
		id(nullptr),
		color(nullptr)
	{
	}

	~element_particle()
	{
		delete type;
		delete id;
		delete color;
	}

	element_particle(
		const int& type,
		const int& id,
		const glm::vec3& color
	) :
		type(new int(type)),
		id(new int(id)),
		color(new glm::vec3(color))
	{}
	
	element_particle(const element_particle& other) = default;

	element_particle(element_particle && other) noexcept
		: type(other.type),
		id(other.id),
		color(other.color)
	{
	}

	element_particle& operator=(const element_particle & other)
	{
		if (this == &other)
			return *this;
		type = other.type;
		id = other.id;
		color = other.color;
		return *this;
	}

	element_particle& operator=(element_particle && other) noexcept
	{
		if (this == &other)
			return *this;
		type = other.type;
		id = other.id;
		color = other.color;
		return *this;
	}
	
	friend std::ostream& operator<<(std::ostream& os, const element_particle& obj) {
		return os
			<< "type: " << *obj.type
			<< " id: " << *obj.id
			<< " color: r = " << obj.color->x << ", g = " << obj.color->y << ", b = " << obj.color->z;
	}
};
#endif
