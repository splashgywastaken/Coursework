#ifndef GAME_H
#define GAME_H

#include "game_level.h"
#include "sprite_renderer.h"
#include "text_renderer.h"

class element_sim
{
public:
	bool keys[1024]{};
	//Screen width and height
	unsigned int width, height;
	float dt;
	bool pause_simulation = false;
	//Sprite renderer object:
	sprite_renderer *renderer;
	//Fonts renderer
	text_renderer* text;
	//Game level object
	game_level *level;
	//Constructor
	element_sim(
		unsigned width,
		unsigned height
	);
	//Destructor
	~element_sim();

	//Initializing element_sim state (load up all shaders e.t.c.)
	void init();
	//Game loop
	void update(float dt);
	void render(int element_id, int brush_radius, glm::vec2 mouse_position) const;
	void clear_level() const;

	void pause();

	void draw_circle(
		int element_id,
		uint32_t cx, 
		uint32_t cy, 
		uint32_t r
	) const;
};
#endif