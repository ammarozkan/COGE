struct GAME_PlaneController
{
	float turning_deegree = 3.0f;
	bool lShift = false;
};

glm::vec3 PlaneController_getRequiredCamera(GAME_Thing* object)
{
	return object->object.position - (object->object.getFront())*4.0f;
}

glm::vec3 PlaneController_getCameraPos(float deltaTime,glm::vec3 cameraPos,float cam_distance,GAME_Thing* object,void* data)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	glm::vec3 alpha_result = cameraPos + (PlaneController_getRequiredCamera(object)-cameraPos)*deltaTime;
	glm::vec3 distance = alpha_result - object->object.position;
	return object->object.position + glm::normalize(distance)*cam_distance;
}

void PlaneController_Update(float deltaTime, GAME_Thing* object, void* data,GLFWwindow*window)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	if(object!=nullptr) 
	{
		float a_speed = glm::length(object->speed);
		PC->turning_deegree = 3.0f/sqrt(abs(a_speed) > 1.0f ? abs(a_speed) : 1.0f);
	}
	PC->lShift = glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
}

void PlaneController_W(float deltaTime,GAME_Thing* object,void* data)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	if(PC->lShift) object->speed += object->object.getFront() * deltaTime * 10.0f;
	else object->speed += object->object.getFront() * deltaTime * 1.0f;
}

void PlaneController_S(float deltaTime,GAME_Thing* object,void* data)
{
	object->speed -= object->object.getFront() * deltaTime * 1.0f;
}

void PlaneController_R(float deltaTime,GAME_Thing* object,void* data)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	object->object.rotateRelative(glm::vec3(1.0, 0.0f, 0.0f),glm::radians(+PC->turning_deegree));
	glm::vec4 rotV = object->object.rotation * glm::vec4(1.0f,0.0f,0.0f,1.0f);
	glm::vec4 n_spd = glm::rotate(glm::mat4(1.0f),glm::radians(+PC->turning_deegree),glm::vec3(rotV.x,rotV.y,rotV.z)) * glm::vec4(object->speed.x,object->speed.y,object->speed.z,1.0f);
	object->speed = glm::vec3(n_spd.x,n_spd.y,n_spd.z);
}

void PlaneController_F(float deltaTime,GAME_Thing* object,void* data)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	object->object.rotateRelative(glm::vec3(1.0, 0.0f, 0.0f),glm::radians(-PC->turning_deegree));
	glm::vec4 rotV = object->object.rotation * glm::vec4(1.0f,0.0f,0.0f,1.0f);
	glm::vec4 n_spd = glm::rotate(glm::mat4(1.0f),glm::radians(-PC->turning_deegree),glm::vec3(rotV.x,rotV.y,rotV.z)) * glm::vec4(object->speed.x,object->speed.y,object->speed.z,1.0f);
	object->speed = glm::vec3(n_spd.x,n_spd.y,n_spd.z);
}

void PlaneController_A(float deltaTime,GAME_Thing* object,void* data)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	object->object.rotateRelative(glm::vec3(0.0, 0.0f,-1.0f),glm::radians(+PC->turning_deegree/2));
}

void PlaneController_D(float deltaTime,GAME_Thing* object,void* data)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	object->object.rotateRelative(glm::vec3(0.0, 0.0f,-1.0f),glm::radians(-PC->turning_deegree/2));
}

GAME_Controller get_PlaneController(GAME_PlaneController* planeController)
{
	GAME_Controller controller;
	controller.variable = (void*)planeController;

	
	controller.getCameraPos_p = &PlaneController_getCameraPos;
	controller.update_p = &PlaneController_Update;
	controller.W_p = &PlaneController_W;
	controller.S_p = &PlaneController_S;
	controller.R_p = &PlaneController_R;
	controller.F_p = &PlaneController_F;
	controller.A_p = &PlaneController_A;
	controller.D_p = &PlaneController_D;
	controller.LEFT_SHIFT_p = &EMPTY_KEY_FUNCTION;
	controller.ENTER_p = &EMPTY_KEY_FUNCTION;

	return controller;
}