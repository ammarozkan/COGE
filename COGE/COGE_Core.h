namespace COGE
{
	class Engine
	{
	private:
		// GL
		GLFWwindow* window;

		// Files
		DataReader data_reader;

		// Drawing Necessary
		GLS::ShaderProgram* generalShader;
		GLS::Camera camera; glm::mat4 full_projection, far_projection;

		// UI
		GLS::ShaderProgram *UIShader;
		Text DebugText;

		// World
		GAME_Physics world;
		GAME_Terrain terrain, low_terrain;
		std::vector<GAME_Forest> forests;

		// Controllers
		GAME_PlaneController planeController;
		GAME_Controller controller;

		// Objects
		std::vector<GAME_Thing> planes;

		// Uniforms
		unsigned int xEffect, yEffect, zEffect; //these are uniform location of the coordinate base coloring variables
		unsigned int xyzEffects[3]; // complete package of the locations

		// for threads
		bool loading = false;
	public:
		static GLFWwindow* init_gl()
		#include "COGE_OPENGL_INITIALIZER.h"

		void init_files();
		void init_shaders();
		void init_projection();
		void init_terrain();
		void init_objects();
		void init_controllers();
		void init_UI();
		void init();
		void initializing(); // Screen Loop

		Engine(GLFWwindow* window);

		void Work();
		void inStart();
		void inLoop(float deltaTime); 
		// I'm going to define here a loop_th1 and loop_th2 or more for speed. and then loop_th_final for finalizing.
		// and then the threads will came out
		//void loop_th1(float deltaTime); void loop_th2(float deltaTime); void loop_th_final(float deltaTime);

		void Controls(float deltaTime);
		void Draw();
		void Draw_low();
		void Draw_UI();
		void OncePrint(float deltaTime);

	};
}

#include "COGE_Initializers.h"

void COGE::Engine::Work()
{
	float deltaTime;
	float preTime = 0.0f;

	float printTimer = 0.0f;
	LOG("GOING TO LOOP!");
	inStart();
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		deltaTime = glfwGetTime() - preTime;
		preTime = glfwGetTime();

		inLoop(deltaTime);

		//Draw_low();
		//glClear(GL_DEPTH_BUFFER_BIT);
		Draw();
		glClear(GL_DEPTH_BUFFER_BIT);
		Draw_UI();

		glfwSwapBuffers(window);
		glfwPollEvents();

		Controls(deltaTime);

		printTimer+=deltaTime;
		if(printTimer>1.0f)
		{
			OncePrint(deltaTime);
			printTimer = 0.0f;
		}
	}
	glfwTerminate();
}

void COGE::Engine::Controls(float deltaTime)
{
	static unsigned id = 0;
	if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) controller.W(deltaTime);
	if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) controller.S(deltaTime);
	if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) controller.A(deltaTime);
	if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) controller.D(deltaTime);
	if(glfwGetKey(window,GLFW_KEY_R) == GLFW_PRESS) controller.R(deltaTime);
	if(glfwGetKey(window,GLFW_KEY_F) == GLFW_PRESS) controller.F(deltaTime);
	if(glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS) controller.ENTER(deltaTime);
	//if(glfwGetKey(window,GLFW_KEY_C) == GLFW_PRESS) updateCam = false;
	//else updateCam = true;
}

// PROGRAM

void COGE::Engine::inStart()
{
	planes[0].drawer->position = glm::vec3(650.0f,2.0f,0.0f);
	planes[0].drawer->scale = glm::vec3(0.25f,0.25f,0.25f);
	planes[0].drawer->modelRefresh();
	planes[1].drawer->position = glm::vec3(650.0f,2.0f,10.0f);
	planes[2].drawer->position = glm::vec3(650.0f,2.0f,20.0f);
	for(unsigned int i=0;i<planes.size();i++)
	{
		planes[i].drawer->position.y = terrain.getHeight(planes[i].drawer->position.x, planes[i].drawer->position.z)+1.0f;
	}

	camera.updateByTarget(glm::vec3(0.0f));
}

void COGE::Engine::inLoop(float deltaTime)
{
	for(unsigned int i=0;i<planes.size();i++)
	{
		float ideal_height = terrain.getHeight(planes[i].drawer->position.x,planes[i].drawer->position.z)+0.2f;
		planes[i].update(deltaTime, ideal_height);
	}

	if (camera.position.y < terrain.getHeight(camera.position.x,camera.position.z)+0.1f) 
		camera.position.y = terrain.getHeight(camera.position.x,camera.position.z)+0.1f;

	controller.update(deltaTime,window);
	camera.position = controller.getCameraPos(deltaTime, camera.position,3.0f);
	camera.updateByTarget(controller.object->drawer->position);

}

void COGE::Engine::Draw_low()
{
	generalShader->use();
	glUniformMatrix4fv(generalShader->projection, 1, GL_FALSE, glm::value_ptr(far_projection));
	low_terrain.draw(*generalShader,xyzEffects);
}

void COGE::Engine::Draw()
{
	generalShader->use();

	glUniformMatrix4fv(generalShader->view, 1, GL_FALSE, glm::value_ptr(camera.getView()));
	glUniformMatrix4fv(generalShader->projection, 1, GL_FALSE, glm::value_ptr(full_projection));


	glUniform3f(xEffect, 0.0f, 0.0f, 0.0f);
	glUniform3f(yEffect, 0.0f, 0.0f, 0.0f);
	glUniform3f(zEffect, 1.0f, 0.0f, 0.0f);
	for(unsigned int i = 0; i<planes.size();i++)
	{
		planes[i].drawer->modelRefresh();
		planes[i].drawer->shader_model(generalShader->model);
		planes[i].drawer->drawElements();
	}

	terrain.draw(*generalShader,xyzEffects);
	for(unsigned int i = 0;i<forests.size();i++) forests[i].draw(*generalShader,xyzEffects);
}

void COGE::Engine::Draw_UI()
{
	UIShader->use();
	DebugText.draw_test(*UIShader);
}

void COGE::Engine::OncePrint(float deltaTime)
{
	LOG("FPS:" << 1.0f/deltaTime);
}