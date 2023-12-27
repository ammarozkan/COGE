#include <COGE/controller/planecontroller.h>
#include <COGE/Macros.h>

glm::vec3 PlaneController_getRequiredCamera(GAME_Thing* target,GAME_PlaneController *PC)
{
	if(PC->countdown < 0.0f)
	{
		glm::vec3 front = target->object.getFront();
		PC->cam_direction = glm::vec4(front.x,front.y,front.z,1.0f);
		PC->cam_matrix = glm::mat4(1.0f);
	}
	//return target->object.position - *glm::normalize(glm::vec3(PC->cam_direction));
	return target->object.position - glm::normalize(glm::vec3(PC->cam_direction));
}

glm::vec3 PlaneController_getCameraPos(float deltaTime,glm::vec3 cameraPos,float cam_distance,GAME_Thing* target,void* data)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	glm::vec3 alpha_result = PlaneController_getRequiredCamera(target,PC);
	if(PC->countdown < 0.0f)  alpha_result = cameraPos + (alpha_result-cameraPos)*deltaTime;
	glm::vec3 distance = alpha_result - target->object.position;
	return target->object.position + glm::normalize(distance)*cam_distance;
	return PlaneController_getRequiredCamera(target,PC);
}

void PlaneController_Update(float deltaTime, GAME_Thing* target, void* data,GLFWwindow*window)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	if(target!=nullptr) 
	{
		float a_speed = glm::length(target->speed);
		PC->turning_deegree = 3.0f/sqrt(abs(a_speed) > 1.0f ? abs(a_speed) : 1.0f);
	}
	PC->lShift = glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
	PC->countdown -= deltaTime;
}

void PlaneController_W(float deltaTime,GAME_Thing* target,void* data)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	if(PC->lShift) target->speed += target->object.getFront() * deltaTime * 1.0f;
	else target->speed += target->object.getFront() * deltaTime * 0.5f;
}

void PlaneController_S(float deltaTime,GAME_Thing* target,void* data)
{
	target->speed -= target->object.getFront() * deltaTime * 0.5f;
}

void PlaneController_R(float deltaTime,GAME_Thing* target,void* data)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	target->object.rotateRelative(glm::vec3(1.0, 0.0f, 0.0f),glm::radians(+PC->turning_deegree));
	glm::vec4 rotV = target->object.rotation * glm::vec4(1.0f,0.0f,0.0f,1.0f);
	glm::vec4 n_spd = glm::rotate(glm::mat4(1.0f),glm::radians(+PC->turning_deegree),glm::vec3(rotV.x,rotV.y,rotV.z)) * glm::vec4(target->speed.x,target->speed.y,target->speed.z,1.0f);
	target->speed = glm::vec3(n_spd.x,n_spd.y,n_spd.z);
}

void PlaneController_F(float deltaTime,GAME_Thing* target,void* data)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	target->object.rotateRelative(glm::vec3(1.0, 0.0f, 0.0f),glm::radians(-PC->turning_deegree));
	glm::vec4 rotV = target->object.rotation * glm::vec4(1.0f,0.0f,0.0f,1.0f);
	glm::vec4 n_spd = glm::rotate(glm::mat4(1.0f),glm::radians(-PC->turning_deegree),glm::vec3(rotV.x,rotV.y,rotV.z)) * glm::vec4(target->speed.x,target->speed.y,target->speed.z,1.0f);
	target->speed = glm::vec3(n_spd.x,n_spd.y,n_spd.z);
}

void PlaneController_A(float deltaTime,GAME_Thing* target,void* data)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	target->object.rotateRelative(glm::vec3(0.0, 0.0f,-1.0f),glm::radians(+PC->turning_deegree/2));
}

void PlaneController_D(float deltaTime,GAME_Thing* target,void* data)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	target->object.rotateRelative(glm::vec3(0.0, 0.0f,-1.0f),glm::radians(-PC->turning_deegree/2));
}

void PlaneController_MOUSE(float deltaTime,GAME_Thing* target,void* data,float velx, float vely)
{
	GAME_PlaneController *PC = ((GAME_PlaneController*)data);
	if(velx!=0.0f or vely!=0.0f) PC->countdown = 2.0f;
	PC->cam_direction = glm::rotate(glm::mat4(1.0f),glm::radians(1000.0f*deltaTime*velx/WIDTH),glm::vec3(0.0f,1.0f,0.0f)) * PC->cam_direction;
	//PC->cam_direction = glm::rotate(glm::mat4(1.0f),glm::radians(deltaTime*vely/HEIGHT),glm::vec3(1.0f,0.0f,0.0f)) * PC->cam_direction;
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
	controller.MOUSE_p = &PlaneController_MOUSE;
	controller.getCameraTarget_p = &DEFAULT_CAMERATARGET_FUNCTION;

	return controller;
}