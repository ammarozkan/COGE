#include <COGE/controller/tpscontroller.h>

glm::vec3 TPSController_getCameraTarget(float deltaTime, GAME_Thing* object, void* data)
{
	GAME_TPSController *PC = ((GAME_TPSController*)data);
	return object->object.position + object->object.getRight()*0.25f + glm::vec3(0.0f,0.25f,0.0f);
}

glm::vec3 TPSController_getRequiredCamera(GAME_Thing* object)
{
	return object->object.position - object->object.getFront()*5.0f + object->object.getRight()*0.25f + glm::vec3(0.0f,1.0f,0.0f);
}

glm::vec3 TPSController_getCameraPos(float deltaTime,glm::vec3 cameraPos,float cam_distance,GAME_Thing* object,void* data)
{
	GAME_TPSController *PC = ((GAME_TPSController*)data);
	glm::vec3 alpha_result = cameraPos + (TPSController_getRequiredCamera(object)-cameraPos)*deltaTime;
	glm::vec3 target = TPSController_getCameraTarget(deltaTime,object,data);
	glm::vec3 distance = alpha_result - target; // may slow the process
	return target + glm::normalize(distance)*cam_distance;
}

void TPSController_Update(float deltaTime, GAME_Thing* object, void* data,GLFWwindow*window)
{
	GAME_TPSController *PC = ((GAME_TPSController*)data);
}

void TPSController_W(float deltaTime,GAME_Thing* object,void* data)
{
	GAME_TPSController *PC = ((GAME_TPSController*)data);
	object->object.position += object->object.getFront() * deltaTime * 1.0f;
}

void TPSController_S(float deltaTime,GAME_Thing* object,void* data)
{
	GAME_TPSController *PC = ((GAME_TPSController*)data);
	object->object.position -= object->object.getFront() * deltaTime * 1.0f;
}

void TPSController_R(float deltaTime,GAME_Thing* object,void* data)
{
	GAME_TPSController *PC = ((GAME_TPSController*)data);
}

void TPSController_F(float deltaTime,GAME_Thing* object,void* data)
{
	GAME_TPSController *PC = ((GAME_TPSController*)data);
}

void TPSController_A(float deltaTime,GAME_Thing* object,void* data)
{
	GAME_TPSController *PC = ((GAME_TPSController*)data);
	object->object.rotateRelative(glm::vec3(0.0f,1.0f,0.0f),glm::radians(+180.0f)*deltaTime);
}

void TPSController_D(float deltaTime,GAME_Thing* object,void* data)
{
	GAME_TPSController *PC = ((GAME_TPSController*)data);
	object->object.rotateRelative(glm::vec3(0.0f,1.0f,0.0f),glm::radians(-180.0f)*deltaTime);
}

GAME_Controller get_TPSController(GAME_TPSController* TPSController)
{
	GAME_Controller controller;
	controller.variable = (void*)TPSController;

	
	controller.getCameraPos_p = &TPSController_getCameraPos;
	controller.update_p = &TPSController_Update;
	controller.W_p = &TPSController_W;
	controller.S_p = &TPSController_S;
	controller.R_p = &TPSController_R;
	controller.F_p = &TPSController_F;
	controller.A_p = &TPSController_A;
	controller.D_p = &TPSController_D;
	controller.LEFT_SHIFT_p = &EMPTY_KEY_FUNCTION;
	controller.ENTER_p = &EMPTY_KEY_FUNCTION;
	controller.MOUSE_p = &EMPTY_MOUSE_FUNCTION;
	controller.getCameraTarget_p = &TPSController_getCameraTarget;

	return controller;
}
