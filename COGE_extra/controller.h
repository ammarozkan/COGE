struct GAME_Controller
{
	GAME_Thing* object;
	void* variable;
	GAME_Controller(){object = nullptr;}

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

	glm::vec3 getCameraPos(float deltaTime,glm::vec3 cameraPos,float distance) {return getCameraPos_p(deltaTime,cameraPos,distance,object,variable);}
	void update(float deltaTime,GLFWwindow*window) {update_p(deltaTime,object,variable,window);}
	void W(float deltaTime) {W_p(deltaTime,object,variable);}
	void S(float deltaTime) {S_p(deltaTime,object,variable);}
	void R(float deltaTime) {R_p(deltaTime,object,variable);}
	void F(float deltaTime) {F_p(deltaTime,object,variable);}
	void A(float deltaTime) {A_p(deltaTime,object,variable);}
	void D(float deltaTime) {D_p(deltaTime,object,variable);}
	void LEFT_SHIFT(float deltaTime) {LEFT_SHIFT_p(deltaTime,object,variable);}
	void ENTER(float deltaTime) {ENTER_p(deltaTime,object,variable);}
};

void EMPTY_KEY_FUNCTION(float deltaTime,GAME_Thing* object,void* data){}

// PLANE CONTROLLER

#include "Controllers/planecontroller.h"

#include "Controllers/tpscontroller.h"