void COGE::Engine::init_files()
{
	LOG("FILE INITIALIZATION");
	// this file includes
			// generalshader.glsl
			// defaultshader.glsl
			// testshader.glsl
			// uishader.glsl
			// model_plane
	data_reader.addFile("packages/early_package.COGE");
}

void COGE::Engine::init_shaders()
{
	LOG("SHADER INITIALIZATION");
	GLS::ShaderText general_shader_data = data_reader.read_shader("generalshader");
	generalShader = new GLS::ShaderProgram(general_shader_data.vertex.c_str(),general_shader_data.fragment.c_str());

	E_LOG(general_shader_data.vertex);
	E_LOG(general_shader_data.fragment);
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
	terrain.terrain->scale = glm::vec3(2500.0f*5.0f,100.0f,2500.0f*5.0f);
	terrain.terrain->position = glm::vec3(0.0f,-50.0f,0.0f);
	low_terrain.terrain->scale = glm::vec3(2500.0f*5.0f,100.0f,2500.0f*5.0f);
	low_terrain.terrain->position = glm::vec3(0.0f,-50.0f,0.0f);

	GLS::MODEL model_TreeGrass = data_reader.read_model("model_tree_grass"),
		model_TreeWood = data_reader.read_model("model_tree_wood");
	forests.push_back(GAME_Forest(1000, 100.0f, 100.0f, 650.0f, 0.0f, terrain,model_TreeGrass,model_TreeWood));
}

void COGE::Engine::init_objects()
{
	GLS::MODEL plane = data_reader.read_model("model_plane");
	LOG("OBJECT INITIALIZATION");
	planes.push_back(GAME_Thing(new GLS::Drawer(plane, GL_STATIC_DRAW), &world));
	planes.push_back(GAME_Thing(new GLS::Drawer(plane, GL_STATIC_DRAW), &world));
	planes.push_back(GAME_Thing(new GLS::Drawer(plane, GL_STATIC_DRAW), &world));
}

void COGE::Engine::init_UI()
{
	LOG("UI INITIALIZATION");
	DebugText.position = glm::vec2(-WIDTH+5.0f,+HEIGHT-25.0f-10.0f);
}

void COGE::Engine::init()
{
	init_files();
	init_shaders();
	init_projection();
	init_terrain();
	init_objects();
	init_controllers();
	init_UI();
	loading = false;
}

COGE::Engine::Engine(GLFWwindow* window) :
	terrain(1000,1000), low_terrain(50,50), DebugText("A",25.0f)
{
	if(window == nullptr)
	{
		WARN("OPENGL INITIALIZATION FAILED.");
		return;
	}
	this->window = window;

	loading = true;
	//std::thread th_initializing(&Engine::initializing,this);

	//initializing(); //th_initializing.join();
	init();
	// waiting for multi threaded initialization. in example for loading screen?
}

void COGE::Engine::initializing()
{
	float deltaTime;
	float preTime = 0.0f,printTimer=0.0f;

	float triangle_vertices[] = {
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int triangle_indices[] = {0,1,2};

	GLS::Drawer triangle_that_spins(sizeof(triangle_vertices),triangle_vertices,sizeof(triangle_indices),triangle_indices,GL_STATIC_DRAW);

	while(!glfwWindowShouldClose(window) and loading)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		deltaTime = glfwGetTime() - preTime;
		preTime = glfwGetTime();

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