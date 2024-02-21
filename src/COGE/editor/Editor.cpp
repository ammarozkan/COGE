#include <COGE/editor/Editor.h>
#include <COGE/Macros.h>


namespace COGE
{
	Editor::Editor(GLFWwindow* window) : ECE(this)
	{
		if(window==nullptr)
		{
			WARN("GL INITIALIZING IS NOT CORRECTLY DONE."); return;
		}
		this->window = window;


		full_projection = glm::perspective(glm::radians(45.0f),(float)WIDTH/(float)HEIGHT,0.1f,100000.0f);

		data_loader.addFile("packages/early_package.COGE");
		generalRenderer.initShader(data_loader.read_shader("generalshader"));
		generalRenderer.setCamera(&camera);
		generalRenderer.setSky(&sky);
		model = data_loader.load_model("model_plane");
		sky.init_drawer(*model,data_loader.read_shader("skyboxshader"));
		target = new GLS::VideoModel(*model,GL_DYNAMIC_DRAW);
		init_complete = true;
	}

	Editor::~Editor()
	{
		delete model;
		delete UIShader;
		delete target;
	}

	void Editor::ChangeModel(GLS::MODEL& model) { target->data(model,GL_DYNAMIC_DRAW); }

	void Editor::ChangeModel(std::string name) 
	{ 
		delete model;
		model = data_loader.load_model(name);
		ChangeModel(*model);
	}

	void Editor::OncePrint(float deltaTime)
	{
		//LOG("TIME:"<<glfwGetTime());
	}

	void Editor::HandleCommand(std::string command)
	{
		LOG("COMMAND:"<<command);
		ECE.handle(command);
	}

	void Editor::Controls(float deltaTime)
	{
		static bool pre_C = false;
		bool C = glfwGetKey(window,GLFW_KEY_C) == GLFW_PRESS;
		if(C != pre_C && C == true)
		{
			std::string input;
			while(true)
			{
				std::getline(std::cin, input);
				if(input=="PREVIEW") break;
				HandleCommand(input);
			}
		}
		pre_C = C;
	}

	void Editor::Draw_UI()
	{

	}

	void Editor::inLoop(float deltaTime)
	{
		sky.tick();

		camera.position = glm::vec3(sin(glfwGetTime()),sin(glfwGetTime()/5)/2,cos(glfwGetTime()))*seeDistance;
		camera.updateByTarget(glm::vec3(0.0f,0.0f,0.0f));
	}


	void Editor::Work()
	{
		if(!init_complete)
		{
			LOG("EXITING PROGRAM.");
			return;
		}

		float printTimer = 0.0f,deltaTime;

		preTime = glfwGetTime();
		LOG("GOING TO LOOP!");
		while(!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			deltaTime = glfwGetTime() - preTime;
			preTime = glfwGetTime();

			inLoop(deltaTime);

			// SKY
			glClear(GL_DEPTH_BUFFER_BIT);
			sky.draw(camera,full_projection);


			// PREVIEW
			glClear(GL_DEPTH_BUFFER_BIT);
			generalRenderer.use(full_projection);
			generalRenderer.draw(target,obj);

			// UI
			//glClear(GL_DEPTH_BUFFER_BIT);
			//Draw_UI();

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


}