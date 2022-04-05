#ifndef ELEMENT_H
#define ELEMENT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture_2d.h"
#include "sprite_renderer.h"

#include <vector>

/**
 * Базовый абстрактный класс для всех частиц.
 * Используется для задания сетки частиц на экране и для описания базового поведения
 * элементов при работе симцляции
 */
class element
{
	// Основные методы для элементов 
public:
	//данные об объекте
	uint32_t id;
	glm::vec2 position, size, velocity;
	glm::vec3 color;
	bool destroyed;

	// данные о рендере
	texture_2d sprite;

	// конструкторы
	element();
	element(element& element);
	element(
		glm::vec2 pos,
		glm::vec2 size,
		texture_2d sprite,
		glm::vec3 color = glm::vec3(1.0f),
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f)
	);
	virtual ~element() = default;

	virtual void draw(sprite_renderer& renderer);

	// "Шаг" блока в матрице клеточного автомата
	virtual void step(std::vector<std::vector<element*>> elements) = 0;
	virtual bool receive_heat() = 0;

};

inline element::element()
	:
	position(0.0f, 0.0f),
	size(1.0f, 1.0f),
	velocity(0.0f),
	color(1.0f),
	destroyed(false)
{
	
}

inline element::element(element& element) :
	position(element.position),
	size(element.size),
	velocity(element.velocity),
	color(element.color),
	destroyed(element.destroyed),
	sprite(element.sprite)
{

}

inline element::element(
	glm::vec2 pos,
	glm::vec2 size,
	texture_2d sprite,
	glm::vec3 color,
	glm::vec2 velocity
) :
	position(pos),
	size(size),
	velocity(velocity),
	color(color),
	destroyed(false),
	sprite(sprite)
{

}

inline void element::draw(sprite_renderer& renderer)
{
	renderer.draw_sprite(sprite, position, size, 0, color);
}

#endif
