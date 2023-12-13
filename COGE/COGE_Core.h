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
		GLS::ShaderProgram* generalShader; Shader3D generalShader_uniforms;
		GLS::Camera camera; glm::mat4 full_projection, far_projection;

		// UI
		GLS::ShaderProgram *UIShader; ShaderUI UIShader_uniforms;
		Text DebugText;

		// World
		GAME_Physics world;
		GAME_Terrain terrain, low_terrain;

		GAME_Water water;

		std::vector<GAME_Forest> forests;

		// Controllers
		GAME_PlaneController planeController;
		GAME_TPSController tpsController;
		GAME_Controller controller;

		// Objects
		std::vector<GAME_Thing> planes;
		std::vector<GAME_Thing> objects;
		GLS::MODEL* planeModel; // SHOULD PUT THESE THINGS TO A UNORDERED MAP OR SMTH LIKE THAT FOR MODEL LOADING AND REQUIREMENTS... OR
		// JUST IMPLEMENT MODELFINDER CLASS OR SMTH LTHAT

		// Uniforms
		unsigned int xyzEffects[3]; // complete package of the locations

		// for threads
		bool loading = false;

		bool init_complete = false;
		
		// Public variables
		float preTime, deltaTime;
	public:
		static GLFWwindow* init_gl()
		#include "COGE_OPENGL_INITIALIZER.h"

		//static GLFWwindow* init_vulkan(); // u gotta be sh* me

		bool init_files();
		void init_UI();
		void init_shaders();
		void init_projection();
		void init_terrain();
		void init_objects();
		void init_controllers();

		void mainThread_init();
		void threaded_init();
		bool init();
		void initializing(); // Screen Loop

		void menu(); // just main menu

		Engine(GLFWwindow* window);

		void Work();
		void inStart();
		void inLoop(float deltaTime); 
		// I need smth like loop_reader here for threaded file read stuff. So I can read files free from "working"
		// Just need to pass the data loop to loop_reader vice versa.

		void Controls(float deltaTime);
		void Draw();
		void Draw_low();
		void Draw_UI();
		void OncePrint(float deltaTime);

		~Engine();

	};
}

#include "COGE_Initializers.h"

void COGE::Engine::Work()
{
	if(!init_complete)
	{
		LOG("EXITING PROGRAM.");
		return;
	}

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
	planes[0].object.position = glm::vec3(650.0f,2.0f,0.0f);
	planes[0].object.scale = glm::vec3(0.25f,0.25f,0.25f);
	planes[0].object.modelRefresh();
	planes[1].object.position = glm::vec3(650.0f,2.0f,10.0f);
	planes[2].object.position = glm::vec3(650.0f,2.0f,20.0f);
	objects[0].object.position = glm::vec3(650.0f,10.0f,10.0f);
	for(unsigned int i=0;i<planes.size();i++)
	{
		planes[i].object.position.y = terrain.getHeight(planes[i].object.position.x, planes[i].object.position.z)+1.0f;
	}

	camera.updateByTarget(glm::vec3(0.0f));
}

void COGE::Engine::inLoop(float deltaTime)
{

	for(unsigned int i=0;i<planes.size();i++)
	{
		float ideal_height = terrain.getHeight(planes[i].object.position.x,planes[i].object.position.z)+0.2f;
		planes[i].update(deltaTime, ideal_height);
	}

	for(unsigned int i=0;i<objects.size();i++)
	{
		float ideal_height = terrain.getHeight(objects[i].object.position.x,objects[i].object.position.z)+objects[i].object.scale.y/4.0f;
		objects[i].update(deltaTime, ideal_height);
	}

	if (camera.position.y < terrain.getHeight(camera.position.x,camera.position.z)+0.1f) 
		camera.position.y = terrain.getHeight(camera.position.x,camera.position.z)+0.1f;

	controller.update(deltaTime,window);
	camera.position = controller.getCameraPos(deltaTime, camera.position,3.0f);
	camera.updateByTarget(controller.object->object.position);

}

void COGE::Engine::Draw_low()
{
	generalShader->use();
	glUniformMatrix4fv(generalShader_uniforms.projection, 1, GL_FALSE, glm::value_ptr(far_projection));
	low_terrain.draw(generalShader_uniforms,xyzEffects);
}

void COGE::Engine::Draw()
{
	generalShader->use();
	glUniformMatrix4fv(generalShader_uniforms.view, 1, GL_FALSE, glm::value_ptr(camera.getView()));
	glUniformMatrix4fv(generalShader_uniforms.projection, 1, GL_FALSE, glm::value_ptr(full_projection));

	glUniform3f(xyzEffects[0], 0.0f, 0.0f, 0.0f);
	glUniform3f(xyzEffects[1], 0.0f, 0.0f, 0.0f);
	glUniform3f(xyzEffects[2], 1.0f, 0.0f, 0.0f);
	for(unsigned int i = 0; i<planes.size();i++)
	{
		planes[i].object.modelRefresh();
		planes[i].object.shader_model(generalShader_uniforms.model);
		planes[i].drawer->drawElements();
	}

	for(unsigned int i = 0; i<objects.size();i++)
	{
		objects[i].object.modelRefresh();
		objects[i].object.shader_model(generalShader_uniforms.model);
		objects[i].drawer->drawElements();
	}

	terrain.draw(generalShader_uniforms,xyzEffects);
	for(unsigned int i = 0;i<forests.size();i++) forests[i].draw(generalShader_uniforms,xyzEffects);

	water.shader->use();
	water.refresh_projection(full_projection,camera.getView());
	water.draw(preTime);
}

void COGE::Engine::Draw_UI()
{
	UIShader->use();
	DebugText.draw_test(UIShader_uniforms);
}

void COGE::Engine::OncePrint(float deltaTime)
{
	LOG("FPS:" << 1.0f/deltaTime);
	LOG("PPOS:" << controller.object->object.position.x<< controller.object->object.position.y<< controller.object->object.position.z);
	LOG("CPOS:" << camera.position.x<< camera.position.y << camera.position.z);
}