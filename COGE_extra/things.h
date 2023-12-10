struct GAME_Physics
{
	glm::vec3 gravity = glm::vec3(0.0f,-1.00f,0.0f);
};

class GAME_Thing
{
public:
	GLS::Drawer* drawer;
	glm::vec3 speed = glm::vec3(0.0f);
	GAME_Physics* world_physics;

	GAME_Thing(GLS::Drawer* drawer_ptr, GAME_Physics* world_physics)
	{
		this->drawer = drawer_ptr;
		this->world_physics = world_physics;
	}
	void update(float deltaTime,float min_height)
	{
		drawer->position += speed*deltaTime;
		speed+=world_physics->gravity*deltaTime;
		if(drawer->position.y < min_height)
		{
			drawer->position.y = min_height;
			speed -= deltaTime*speed;
			if(speed.y < 0.0f) speed.y = 0.0f;
			drawer->position.y = min_height;
		}
	}
};