#ifndef COGE_CORE_H
#define COGE_CORE_H

// Functions that defined here, will be symbolised under
//		APIInitializers.cpp
//		Initializers.cpp
//		Core.cpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <COGE/drawers_low/GL_LeCamera.hpp>

#include <COGE/datas/DataLoader.hpp>
#include <COGE/debugui/DebugUI.hpp>
#include <COGE/objects/things.h>
#include <COGE/controller/controller.h>

//#include <COGE/objects/generators.h>
#include <COGE/objects/water.h>
#include <COGE/objects/terrain.h>
#include <COGE/objects/tree.h>
//#include <COGE/objects/things.h>

#include <COGE/renderer/StandardShaders.h>
#include <COGE/renderer/Sky.h>
#include <COGE/renderer/General.h>

namespace COGE
{
	class Engine
	{
	private:
		// GL
		GLFWwindow* window;

		// Files
		DataLoader data_loader;

		// Drawing Necessary
		GeneralRenderer generalRenderer;
		GLS::Camera camera; glm::mat4 full_projection, far_projection;

		// UI
		GLS::ShaderProgram *UIShader; ShaderUI UIShader_uniforms;
		Text DebugText;

		// World
		GAME_Physics world;
		GAME_Terrain terrain, low_terrain;
		Sky* sky;

		GAME_Water water;


		std::vector<GAME_Forest*> forests;

		// Controllers
		bool pr = false;
		GAME_PlaneController planeController;
		GAME_TPSController tpsController;

		// Objects
		std::vector<GAME_Thing> planes;
		std::vector<GAME_Thing> objects;
		GLS::MODEL* planeModel; // SHOULD PUT THESE THINGS TO A UNORDERED MAP OR SMTH LIKE THAT FOR MODEL LOADING AND REQUIREMENTS... OR
		// JUST IMPLEMENT MODELFINDER CLASS OR SMTH LTHAT
		GLS::MODEL *model_TreeGrass;
		GLS::MODEL *model_TreeWood;
		GLS::MODEL *model_Flight;

		// Uniforms
		unsigned int xyzEffects[3]; // complete package of the locations

		// for threads
		bool loading = false;

		bool init_complete = false;
		
		// Public variables
		float preTime, deltaTime;

	public:
		static GLFWwindow* init_gl();

		//static GLFWwindow* init_vulkan(); // u gotta be sh* me

		bool init_files();
		void init_UI();
		void init_shaders();
		void init_projection();
		void init_renderers();
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
		void Draw_Skybox();
		void Draw();
		void Draw_low();
		void Draw_UI();
		void OncePrint(float deltaTime);

		//void Work_Editor();
		//void Draw_Editor();
		//void Controls_Editor();


		~Engine();

	};
}


#endif