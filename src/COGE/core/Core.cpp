#include <COGE/core/Core.h>

#include <COGE/Macros.h>

void COGE::Engine::Work()
{
	if(!init_complete)
	{
		LOG("EXITING PROGRAM.");
		return;
	}

	float printTimer = 0.0f;
	inStart();
	preTime = glfwGetTime();
	LOG("GOING TO LOOP!");
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		deltaTime = glfwGetTime() - preTime;
		preTime = glfwGetTime();

		inLoop(deltaTime);

		//Draw_low();
		glClear(GL_DEPTH_BUFFER_BIT);
		Draw_Skybox();
		glClear(GL_DEPTH_BUFFER_BIT);
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
	if(glfwGetKey(window,GLFW_KEY_C) == GLFW_PRESS) 
	{
		if(!pr)
		{
			if(controller.target == &objects[0])
			{
				controller = get_PlaneController(&planeController);
				controller.target = &planes[0];
			}
			else
			{
				controller = get_TPSController(&tpsController);
				controller.target = &objects[0];
			}
			
			pr = true;
		}
	}
	else pr = false;
	glfwGetCursorPos(window,&controller.mouse_posx,&controller.mouse_posy);
}

// PROGRAM

void COGE::Engine::inStart()
{
	planes[0].object.position = glm::vec3(650.0f,2.0f,0.0f);
	planes[0].object.scale = glm::vec3(0.25f,0.25f,0.25f);
	planes[0].object.modelRefresh();
	planes[1].object.position = glm::vec3(650.0f,2.0f,10.0f);
	planes[2].object.position = glm::vec3(650.0f,2.0f,20.0f);
	objects[0].object.position = glm::vec3(650.0f,terrain.getHeight(650.0f,10.0f)+2.0f,10.0f);
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
	camera.position = controller.getCameraPos(deltaTime, camera.position,1.0f);
	camera.updateByTarget(controller.getCameraTarget(deltaTime));

	sunDirection = glm::vec3(0.0f,cos(glfwGetTime()/10),sin(glfwGetTime()/10));
}

void COGE::Engine::Draw_low()
{
	generalShader->use();
	glUniformMatrix4fv(generalShader_uniforms.projection, 1, GL_FALSE, glm::value_ptr(far_projection));
	low_terrain.draw(generalShader_uniforms,xyzEffects);
}



void COGE::Engine::Draw()
{
	glUniform3f(generalShader_uniforms.cameraPosition,camera.position.x,camera.position.y,camera.position.z);
	generalShader->use();
	glUniformMatrix4fv(generalShader_uniforms.view, 1, GL_FALSE, glm::value_ptr(camera.getView()));
	glUniformMatrix4fv(generalShader_uniforms.projection, 1, GL_FALSE, glm::value_ptr(full_projection));
	glUniform3f(generalShader_uniforms.sunDirection, sunDirection.x,sunDirection.y,sunDirection.z);


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
	for(unsigned int i = 0;i<forests.size();i++) forests[i]->draw(generalShader_uniforms,xyzEffects);

	water.shader->use();
	water.refresh_projection(full_projection,camera.getView());
	water.draw(preTime);
}

void COGE::Engine::Draw_UI()
{
	UIShader->use();
	DebugText.draw_test(UIShader_uniforms);
}

void COGE::Engine::Draw_Skybox()
{
	skyboxShader->use();
	glm::mat4 nonPositionalCameraView = glm::mat4(glm::mat3(camera.getView()));
	glUniformMatrix4fv(skyView, 1, GL_FALSE, glm::value_ptr(nonPositionalCameraView));
	glUniformMatrix4fv(skyProj, 1, GL_FALSE, glm::value_ptr(full_projection));
	glUniform3f(skySunDirection, sunDirection.x,sunDirection.y,sunDirection.z);
	anBox->drawElements();
}

void COGE::Engine::OncePrint(float deltaTime)
{
	LOG("FPS:" << 1.0f/deltaTime);
	LOG("PPOS:" << controller.target->object.position.x << " " << controller.target->object.position.y << " " << controller.target->object.position.z);
	LOG("CPOS:" << camera.position.x << " " << camera.position.y << " " << camera.position.z);
}
