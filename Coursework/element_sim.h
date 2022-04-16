#ifndef GAME_H
#define GAME_H

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
	bool pause_simulation = false;
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
	void update(float dt) const;
	void render() const;
	void clear_level() const;

	void pause();

	void draw_circle(
		element_particle* element,
		uint32_t cx, 
		uint32_t cy, 
		uint32_t r
	) const;
};
#endif