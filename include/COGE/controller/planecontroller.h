#ifndef COGE_PLANECONTROLLER_H
#define COGE_PLANECONTROLLER_H

#include <COGE/controller/controller.h>
#include <COGE/Mathematics.h>
#include <GLFW/glfw3.h>

struct GAME_PlaneController
{
	float turning_deegree = 3.0f;
	bool lShift = false;
	glm::vec4 cam_direction = glm::vec4(0.0f,0.0f,1.0f,1.0f);
	glm::mat4 cam_matrix = glm::mat4(1.0f);
	float countdown = 5.0f;
};

GAME_Controller get_PlaneController(GAME_PlaneController* planeController);

#endif