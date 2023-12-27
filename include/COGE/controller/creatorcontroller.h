#ifndef COGE_CREATORCONTROLLER_H
#define COGE_CREATORCONTROLLER_H

#include <COGE/controller/controller.h>


struct GAME_CreatorController
{
	
};

glm::vec3 CreatorController_getRequiredCamera(GAME_Thing* object);

glm::vec3 CreatorController_getCameraPos(float deltaTime,glm::vec3 cameraPos,float cam_distance,GAME_Thing* object,void* data);

void CreatorController_Update(float deltaTime, GAME_Thing* object, void* data,GLFWwindow*window);

void CreatorController_W(float deltaTime,GAME_Thing* object,void* data);

void CreatorController_S(float deltaTime,GAME_Thing* object,void* data);

void CreatorController_R(float deltaTime,GAME_Thing* object,void* data);

void CreatorController_F(float deltaTime,GAME_Thing* object,void* data);

void CreatorController_A(float deltaTime,GAME_Thing* object,void* data);

void CreatorController_D(float deltaTime,GAME_Thing* object,void* data);

GAME_Controller get_CreatorController(GAME_CreatorController* CreatorController);

#endif