#ifndef COGE_THINGS_H
#define COGE_THINGS_H

#include <COGE/Mathematics.h>
#include <COGE/drawers_low/GL_Draw.hpp>

struct GAME_Physics
{
	glm::vec3 gravity = glm::vec3(0.0f,-1.00f,0.0f);
};

class GAME_Thing
{
public:
	GLS::Object3D object;
	GLS::Drawer* drawer;
	glm::vec3 speed = glm::vec3(0.0f);
	GAME_Physics* world_physics;

	GAME_Thing(GLS::Drawer* drawer_ptr, GAME_Physics* world_physics);

	void update(float deltaTime,float min_height);
};

#endif