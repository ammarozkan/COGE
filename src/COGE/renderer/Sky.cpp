#include <COGE/renderer/Sky.h>
#include <COGE/Macros.h>
#include <GLFW/glfw3.h>


namespace COGE
{
	Sky::Sky(float t)
	{
		cycle_speed_multiplier = t;
		sunDirection = glm::vec3(0.0f,1.0f,0.1f);
		anBox = nullptr; skyboxShader = nullptr;
	}

	Sky::~Sky()
	{
		if(anBox!=nullptr) delete anBox;
		if(skyboxShader!=nullptr) delete skyboxShader;
	}

	void Sky::init_drawer(GLS::MODEL& model,GLS::ShaderText shader_text)
	{
		anBox = new GLS::Drawer(model,GL_STATIC_DRAW);

		skyboxShader = new GLS::ShaderProgram(shader_text);
		skyboxShader->use();
		skyView = skyboxShader->UniformLocation("view");
		skyProj = skyboxShader->UniformLocation("projection");
		skySunDirection = skyboxShader->UniformLocation("sunDirection");
	}

	void Sky::draw(GLS::Camera cam,glm::mat4 projection)
	{
		skyboxShader->use();
		glm::mat4 nonPositionalCameraView = glm::mat4(glm::mat3(cam.getView()));
		glUniformMatrix4fv(skyView, 1, GL_FALSE, glm::value_ptr(nonPositionalCameraView));
		glUniformMatrix4fv(skyProj, 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3f(skySunDirection, sunDirection.x,sunDirection.y,sunDirection.z);
		anBox->drawElements();
	}

	void Sky::tick()
	{
		sunDirection = glm::vec3(0.0f,cos(glfwGetTime()*cycle_speed_multiplier),sin(glfwGetTime()*cycle_speed_multiplier));
	}
}