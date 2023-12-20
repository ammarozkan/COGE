#ifndef COGE_CONTROLLER_H
#define COGE_CONTROLLER_H

struct GAME_Controller
{
	GAME_Thing* target;
	void* variable;
	double mouse_posx, mouse_posy;
	GAME_Controller(){target = nullptr;}

	glm::vec3 (*getCameraPos_p)(float,glm::vec3,float,GAME_Thing*,void*);
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

	glm::vec3 getCameraPos(float deltaTime,glm::vec3 cameraPos,float distance) {return getCameraPos_p(deltaTime,cameraPos,distance,target,variable);}
	void update(float deltaTime,GLFWwindow*window) 
	{
		update_p(deltaTime,target,variable,window);
		static double preX, preY; static bool first_update = true;
		if(first_update){first_update = false;preX=mouse_posx;preY=mouse_posy;}
		MOUSE_p(deltaTime,target,variable,mouse_posx-preX,preY-mouse_posy);
		preX = mouse_posx; preY = mouse_posy;
	}
	void W(float deltaTime) {W_p(deltaTime,target,variable);}
	void S(float deltaTime) {S_p(deltaTime,target,variable);}
	void R(float deltaTime) {R_p(deltaTime,target,variable);}
	void F(float deltaTime) {F_p(deltaTime,target,variable);}
	void A(float deltaTime) {A_p(deltaTime,target,variable);}
	void D(float deltaTime) {D_p(deltaTime,target,variable);}
	void LEFT_SHIFT(float deltaTime) {LEFT_SHIFT_p(deltaTime,target,variable);}
	void ENTER(float deltaTime) {ENTER_p(deltaTime,target,variable);}
};


GAME_Controller controller;

void EMPTY_KEY_FUNCTION(float deltaTime,GAME_Thing* target,void* data){}
void EMPTY_MOUSE_FUNCTION(float deltaTime,GAME_Thing* target,void* data,float posx, float posy) {}

// CONTROLLERS

#include <COGE/controller/planecontroller.h>
#include <COGE/controller/tpscontroller.h>

#endif