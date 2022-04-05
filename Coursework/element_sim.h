#ifndef GAME_H
#define GAME_H

#include "element.h"
#include "game_level.h"
#include "game_state.h"
#include "sprite_renderer.h"

class element_sim
{
public:
	//Current element_sim state
	game_state state;
	bool keys[1024]{};
	//Screen width and height
	unsigned int width, height;
	//Sprite renderer object:
	sprite_renderer *renderer;
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
	void render();
	//void manage_input();

	void draw_circle(element* element, uint32_t cx, uint32_t cy, uint32_t r);

	void add_element_to_level(element* element, uint32_t x, uint32_t y);
};
#endif