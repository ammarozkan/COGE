#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <COGE/drawers_low/GL_SimpObjects.hpp>

#define COGE_DONT_FILE_LOG
#include <COGE/Engine.h>

#include <COGE/objects/generators.h>

bool COGE::Engine::init_files()
{
	LOG("FILE INITIALIZATION");
	data_loader.addFile("packages/early_package.COGE");
	// this file includes
			// generalshader.glsl
			// defaultshader.glsl
			// testshader.glsl
			// uishader.glsl
			// model_planed
	// maybe hash it and put it to the server, and try to get access? well dude, that'll be cool.
	return true;
}

void COGE::Engine::init_shaders()
{
	LOG("SHADER INITIALIZATION");
	
	generalShader = new GLS::ShaderProgram(data_loader.read_shader("generalshader"));
	generalShader->use();
	generalShader_uniforms.init(*generalShader);
	xyzEffects[0] = generalShader_uniforms.xEffect;
	xyzEffects[1] = generalShader_uniforms.yEffect;
	xyzEffects[2] = generalShader_uniforms.zEffect;

	skyboxShader = new GLS::ShaderProgram(data_loader.read_shader("skyboxshader"));
	skyboxShader->use();
	skyView = skyboxShader->UniformLocation("view");
	skyProj = skyboxShader->UniformLocation("projection");
}

void COGE::Engine::init_projection()
{
	LOG("PROJECTION INITIALIZATION");
	camera.position = glm::vec3(650.0f, 0.0f, -10.0f);
	camera.updateByTarget(glm::vec3(0.0f));
	full_projection = glm::perspective(glm::radians(45.0f),(float)WIDTH/(float)HEIGHT,0.1f,100000.0f);
	far_projection = glm::perspective(glm::radians(45.0f),(float)WIDTH/(float)HEIGHT,500.0f,100000.0f);
}

void COGE::Engine::init_controllers()
{
	LOG("CONTROLLER INITIALIZATION");
	glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
	controller = get_TPSController(&tpsController);
	controller.target = &objects[0];
}

void COGE::Engine::init_terrain()
{
	LOG("TERRAIN INITIALIZATION");
	terrain.generate(1000,1000);
	low_terrain.generate(50,50);

	planeModel = PlaneModelAllocator(1000,1000);
	PlaneModelGenerator(1000,1000,planeModel);

	terrain.terrain_object.scale = glm::vec3(2500.0f*5.0f,100.0f,2500.0f*5.0f);
	terrain.terrain_object.position = glm::vec3(0.0f,-50.0f,0.0f);
	low_terrain.terrain_object.scale = glm::vec3(2500.0f*5.0f,100.0f,2500.0f*5.0f);
	low_terrain.terrain_object.position = glm::vec3(0.0f,-50.0f,0.0f);
	water.object.scale = glm::vec3(2500.0f*5.0f,100.0f,2500.0f*5.0f);
	water.object.position = glm::vec3(0.0f,-50.0f,0.0f);
}

void COGE::Engine::init_objects()
{
	LOG("OBJECT(MODEL) INITIALIZATION");
	GLS::MODEL* plane = data_loader.load_model("model_plane");
	planes.push_back(GAME_Thing(new GLS::Drawer(*plane, GL_STATIC_DRAW), &world));
	planes.push_back(GAME_Thing(new GLS::Drawer(*plane, GL_STATIC_DRAW), &world));
	planes.push_back(GAME_Thing(new GLS::Drawer(*plane, GL_STATIC_DRAW), &world));
	//delete plane;

	LOG("terrain drawer initializing");
	terrain.init_drawer();
	low_terrain.init_drawer();

	LOG("water drawer initializing");
	water.init_drawer(*planeModel,data_loader.read_shader("watershader"));

	LOG("forest initializion");
	GLS::MODEL* model_TreeGrass = data_loader.load_model("model_tree_grass");
	GLS::MODEL* model_TreeWood = data_loader.load_model("model_tree_wood");
	forests.push_back(GAME_Forest(1000, 100.0f, 100.0f, 650.0f, 0.0f, terrain,*model_TreeGrass,*model_TreeWood));
	objects.push_back(GAME_Thing(new GLS::Drawer(*model_TreeWood, GL_STATIC_DRAW), &world));

	GLS::MODEL* boxModel = data_loader.load_model("model_basic_cube");
	anBox = new GLS::Drawer(*boxModel,GL_STATIC_DRAW);
}

void COGE::Engine::init_UI()
{
	LOG("UI INITIALIZATION");
	DebugText.position = glm::vec2(10.0f,HEIGHT-10.0f);

	UIShader = new GLS::ShaderProgram(data_loader.read_shader("uishader")); UIShader->use();
	UIShader_uniforms.init(*UIShader);
	glUniform2f(UIShader_uniforms.screen_size, WIDTH, HEIGHT); // Maybe completely new UI class for this automation?
}

void COGE::Engine::threaded_init()
{
	init_terrain();
	init_projection();
	loading = false;
}

void COGE::Engine::mainThread_init()
{
	init_shaders(); // That thing is can only be working on the main thread.
	init_objects();
	init_controllers();
}

bool COGE::Engine::init()
{
	if(!init_files())
	{
		WARN("SOMETHING WRONG WITH THE FILES.");
		return false;
	}
	init_UI(); // Loading screen needs UI. Everything needs UI. So initing UI secondly.

	loading = true;
	std::thread th_init(&Engine::threaded_init,this);

	initializing(); 
	th_init.join();
	mainThread_init();
	return true;
}

COGE::Engine::Engine(GLFWwindow* window) :
	DebugText("A",25.0f)
{
	if(window == nullptr)
	{
		WARN("OPENGL INITIALIZATION FAILED.");
		return;
	}
	this->window = window;

	if(!init()) {WARN("INITIALIZATION IS NOT COMPLETED.");}
	else init_complete = true;
}

COGE::Engine::~Engine() {}

void COGE::Engine::initializing()
{
	float deltaTime;
	float preTime = 0.0f,printTimer=0.0f;

	float triangle_vertices[] = {
		+0.4f, -0.4f, 0.0f,
		-0.4f, -0.4f, 0.0f,
		+0.0f,  0.45f, 0.0f
	};

	unsigned int triangle_indices[] = {0,1,2};

	GLS::MODEL* triangle_model = new GLS::MODEL(sizeof(triangle_vertices),triangle_vertices,sizeof(triangle_indices),triangle_indices);

	GLS::Drawer triangle_that_spins(*triangle_model,GL_STATIC_DRAW);
	LOG("LOADING SCREEN.");
	glm::mat4 loading_transform = glm::mat4(1.0f);

	while(!glfwWindowShouldClose(window) && loading)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		deltaTime = glfwGetTime() - preTime;
		preTime = glfwGetTime();

		UIShader->use();
		UIShader_uniforms.setPos(glm::vec2(WIDTH-50.0f, 50.0f));
		UIShader_uniforms.setSize(glm::vec2(25.0f,25.0f));
		loading_transform = glm::rotate(loading_transform, glm::radians(50.0f*deltaTime), glm::vec3(0.0f,0.0f,1.0f));
		glUniformMatrix4fv(UIShader_uniforms.transform, 1, GL_FALSE, glm::value_ptr(loading_transform));
		// loading specific shader
		triangle_that_spins.drawElements();

		glfwSwapBuffers(window);
		glfwPollEvents();

		printTimer+=deltaTime;
		if(printTimer>1.0f)
		{
			LOG("LOADING...");
			printTimer = 0.0f;
		}
	}
}