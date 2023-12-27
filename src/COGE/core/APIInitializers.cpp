#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <COGE/drawers_low/GL_SimpObjects.hpp>

#define COGE_DONT_FILE_LOG
#include <COGE/Engine.h>


GLFWwindow* COGE::Engine::init_gl(){
	LOG("OPENGL INITIALIZATION");
	GLFWwindow* window;
	if(!glfwInit()) return nullptr;

	window = glfwCreateWindow(WIDTH,HEIGHT,"COGE",NULL,NULL);

	if(!window)
	{
		WARN("GLFW WINDOW CREATION FAILED.");
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) 
	{
		WARN("GLEW IS NOT OK:"); PRINT(glewGetString(err));
		//return err;
		return nullptr;
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	return window;
}