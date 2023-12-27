#include <COGE/objects/things.h>

GAME_Thing::GAME_Thing(GLS::Drawer* drawer_ptr, GAME_Physics* world_physics)
{
	this->drawer = drawer_ptr;
	this->world_physics = world_physics;
}

void GAME_Thing::update(float deltaTime,float min_height)
{
	object.position += speed*deltaTime;
	speed+=world_physics->gravity*deltaTime;
	if(object.position.y < min_height)
	{
		object.position.y = min_height;
		if(deltaTime < 1.0) speed -= deltaTime*speed;
		if(speed.y < 0.0f) speed.y = 0.0f;
		object.position.y = min_height;
	}
}