#ifndef COGE_SKY_H
#define COGE_SKY_H

#include <COGE/Mathematics.h>

#include <COGE/drawers_low/GL_Shaders.hpp>
#include <COGE/drawers_low/GL_LeCamera.hpp>
#include <COGE/drawers_low/GL_VideoModel.hpp>

namespace COGE
{
	class Sky
	{
	private:
		GLS::ShaderProgram* skyboxShader; unsigned int skyView, skyProj, skySunDirection;
		GLS::VideoModel *anBox;
		float cycle_speed_multiplier;
	public:
		glm::vec3 sunDirection;
		Sky(float cycle_speed = 0.1); ~Sky();

		void init_drawer(GLS::MODEL& skyboxModel,GLS::ShaderText);
		void tick();
		void draw(GLS::Camera,glm::mat4);
	};
}

#endif