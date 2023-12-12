void COGE::Engine::init_files()
{
	LOG("FILE INITIALIZATION");
	data_reader.addFile("packages/early_package.COGE");
	// this file includes
			// generalshader.glsl
			// defaultshader.glsl
			// testshader.glsl
			// uishader.glsl
			// model_planed
}

void COGE::Engine::init_shaders()
{
	LOG("SHADER INITIALIZATION");
	GLS::ShaderText general_shader_data = data_reader.read_shader("generalshader");
	generalShader = new GLS::ShaderProgram(general_shader_data.vertex.c_str(),general_shader_data.fragment.c_str());

	generalShader->use();
	generalShader->initGenericUniforms();
	xEffect = generalShader->UniformLocation("xEffect");
	yEffect = generalShader->UniformLocation("yEffect");
	zEffect = generalShader->UniformLocation("zEffect");
	xyzEffects[0] = xEffect;
	xyzEffects[1] = yEffect;
	xyzEffects[2] = zEffect;

	UIShader = new GLS::ShaderProgram("uishader.glsl");
	UIShader->use(); UIShader->initGenericUniforms();
	glm::mat4 screen_text_scalar = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f/WIDTH,1.0f/HEIGHT,1.0f));
	glUniformMatrix4fv(UIShader->projection, 1, GL_FALSE, glm::value_ptr(screen_text_scalar));
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
	controller = get_PlaneController(&planeController);
	controller.object = &planes[0];
}

void COGE::Engine::init_terrain()
{
	LOG("TERRAIN INITIALIZATION");
	terrain.generate(1000,1000);
	low_terrain.generate(50,50);

	terrain.terrain->scale = glm::vec3(2500.0f*5.0f,100.0f,2500.0f*5.0f);
	terrain.terrain->position = glm::vec3(0.0f,-50.0f,0.0f);
	low_terrain.terrain->scale = glm::vec3(2500.0f*5.0f,100.0f,2500.0f*5.0f);
	low_terrain.terrain->position = glm::vec3(0.0f,-50.0f,0.0f);
}

void COGE::Engine::init_objects()
{
	LOG("OBJECT(MODEL) INITIALIZATION");
	GLS::MODEL plane = data_reader.read_model("model_plane");
	planes.push_back(GAME_Thing(new GLS::Drawer(plane, GL_STATIC_DRAW), &world));
	planes.push_back(GAME_Thing(new GLS::Drawer(plane, GL_STATIC_DRAW), &world));
	planes.push_back(GAME_Thing(new GLS::Drawer(plane, GL_STATIC_DRAW), &world));

	terrain.init_drawer();
	low_terrain.init_drawer();

	GLS::MODEL model_TreeGrass = data_reader.read_model("model_tree_grass"),
		model_TreeWood = data_reader.read_model("model_tree_wood");
	forests.push_back(GAME_Forest(1000, 100.0f, 100.0f, 650.0f, 0.0f, terrain,model_TreeGrass,model_TreeWood));
}

void COGE::Engine::init_UI()
{
	LOG("UI INITIALIZATION");
	DebugText.position = glm::vec2(-WIDTH+5.0f,+HEIGHT-25.0f-10.0f);
}

void COGE::Engine::threaded_init()
{
	init_terrain();
	init_projection();
	init_UI();
	loading = false;
}

void COGE::Engine::mainThread_init()
{
	init_shaders(); // That thing is can only be working on the main thread.
	init_objects();
	init_controllers();
}

void COGE::Engine::init()
{
	init_files(); // scanning files are really important.

	loading = true;
	std::thread th_init(&Engine::threaded_init,this);

	initializing(); 
	th_init.join();
	mainThread_init();
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

	init();

	// waiting for multi threaded initialization. in example for loading screen?
}

COGE::Engine::~Engine() {}

void COGE::Engine::initializing()
{
	float deltaTime;
	float preTime = 0.0f,printTimer=0.0f;

	float triangle_vertices[] = {
		 0.4f, -0.4f, 0.0f,
		-0.4f, -0.4f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int triangle_indices[] = {0,1,2};

	GLS::MODEL triangle_model(sizeof(triangle_vertices),triangle_vertices,sizeof(triangle_indices),triangle_indices);

	GLS::Drawer triangle_that_spins(triangle_model,GL_STATIC_DRAW);
	LOG("LOADING SCREEN.");
	glm::mat4 loading_transform = glm::mat4(1.0f);

	unsigned int UI_screen_size,UI_object_size,UI_position,UI_transform;
	GLS::ShaderText test_shader_data = data_reader.read_shader("test_loading_shader");
	GLS::ShaderProgram *TestShader = new GLS::ShaderProgram(test_shader_data.vertex.c_str(),test_shader_data.fragment.c_str());
	TestShader->use();
	UI_screen_size = TestShader->UniformLocation("screen_size");
	UI_object_size = TestShader->UniformLocation("object_size");
	UI_position = TestShader->UniformLocation("position");
	UI_transform = TestShader->UniformLocation("transform");
	glUniform2f(UI_screen_size, WIDTH, HEIGHT);

	while(!glfwWindowShouldClose(window) && loading)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		deltaTime = glfwGetTime() - preTime;
		preTime = glfwGetTime();

		TestShader->use();
		glUniform2f(UI_object_size, 25.0f, 25.0f);
		glUniform2f(UI_position, WIDTH-50.0f, 50.0f);
		loading_transform = glm::rotate(loading_transform, glm::radians(50.0f*deltaTime), glm::vec3(0.0f,0.0f,1.0f));
		glUniformMatrix4fv(UI_transform, 1, GL_FALSE, glm::value_ptr(loading_transform));
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