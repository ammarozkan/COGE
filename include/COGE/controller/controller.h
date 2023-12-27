#ifndef COGE_CONTROLLER_H
#define COGE_CONTROLLER_H

#include <COGE/objects/things.h>
#include <COGE/Mathematics.h>
#include <GLFW/glfw3.h>

struct GAME_Controller
{
	GAME_Thing* target;
	void* variable;
	double mouse_posx, mouse_posy;
	GAME_Controller(){target = nullptr;}

	glm::vec3 (*getCameraPos_p)(float,glm::vec3,float,GAME_Thing*,void*);
	glm::vec3 (*getCameraTarget_p)(float,GAME_Thing*,void*);
	void (*update_p)(float,GAME_Thing*,void*,GLFWwindow*);
	void (*W_p)(float,GAME_Thing*,void*);
	void (*S_p)(float,GAME_Thing*,void*);
	void (*R_p)(float,GAME_Thing*,void*);
	void (*F_p)(float,GAME_Thing*,void*);
	void (*A_p)(float,GAME_Thing*,void*);
	void (*D_p)(float,GAME_Thing*,void*);
	void (*LEFT_SHIFT_p)(float,GAME_Thing*,void*);
	void (*ENTER_p)(float,GAME_Thing*, void*);
	void (*MOUSE_p)(float,GAME_Thing*, void*, float, float);

	glm::vec3 getCameraPos(float deltaTime,glm::vec3 cameraPos,float distance);
	glm::vec3 getCameraTarget(float deltaTime);
	void update(float deltaTime,GLFWwindow*window);
	void W(float deltaTime);
	void S(float deltaTime);
	void R(float deltaTime);
	void F(float deltaTime);
	void A(float deltaTime);
	void D(float deltaTime);
	void LEFT_SHIFT(float deltaTime);
	void ENTER(float deltaTime);
};


extern GAME_Controller controller;

void EMPTY_KEY_FUNCTION(float deltaTime,GAME_Thing* target,void* data);
void EMPTY_MOUSE_FUNCTION(float deltaTime,GAME_Thing* target,void* data,float posx, float posy);
glm::vec3 DEFAULT_CAMERATARGET_FUNCTION(float deltaTime,GAME_Thing*, void* data);

// CONTROLLERS

#include <COGE/controller/planecontroller.h>
#include <COGE/controller/tpscontroller.h>

#endif