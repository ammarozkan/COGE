#include <COGE/controller/controller.h>

#include <COGE/Mathematics.h>

#include <GLFW/glfw3.h>


void GAME_Controller::W(float deltaTime) {W_p(deltaTime,target,variable);}
void GAME_Controller::S(float deltaTime) {S_p(deltaTime,target,variable);}
void GAME_Controller::R(float deltaTime) {R_p(deltaTime,target,variable);}
void GAME_Controller::F(float deltaTime) {F_p(deltaTime,target,variable);}
void GAME_Controller::A(float deltaTime) {A_p(deltaTime,target,variable);}
void GAME_Controller::D(float deltaTime) {D_p(deltaTime,target,variable);}
void GAME_Controller::LEFT_SHIFT(float deltaTime) {LEFT_SHIFT_p(deltaTime,target,variable);}
void GAME_Controller::ENTER(float deltaTime) {ENTER_p(deltaTime,target,variable);}

glm::vec3 GAME_Controller::getCameraPos(float deltaTime,glm::vec3 cameraPos,float distance) 
	{return getCameraPos_p(deltaTime,cameraPos,distance,target,variable);}

glm::vec3 GAME_Controller::getCameraTarget(float deltaTime) 
	{return getCameraTarget_p(deltaTime,target,variable);}


void GAME_Controller::update(float deltaTime,GLFWwindow*window) 
{
	update_p(deltaTime,target,variable,window);
	static double preX, preY; static bool first_update = true;
	if(first_update){first_update = false;preX=mouse_posx;preY=mouse_posy;}
	MOUSE_p(deltaTime,target,variable,mouse_posx-preX,preY-mouse_posy);
	preX = mouse_posx; preY = mouse_posy;
}

GAME_Controller controller;

void EMPTY_KEY_FUNCTION(float deltaTime,GAME_Thing* target,void* data){}
void EMPTY_MOUSE_FUNCTION(float deltaTime,GAME_Thing* target,void* data,float posx, float posy){}
glm::vec3 DEFAULT_CAMERATARGET_FUNCTION(float deltaTime, GAME_Thing* target, void* data)
{
	return target->object.position;
}
