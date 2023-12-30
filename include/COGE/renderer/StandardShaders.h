#ifndef COGE_STANDARDSHADERS_H
#define COGE_STANDARDSHADERS_H

#include <GL/glew.h>


#include <COGE/Mathematics.h>
#include <COGE/drawers_low/GL_SimpObjects.hpp>
#include <COGE/drawers_low/GL_Shaders.hpp>
#include <COGE/drawers_low/GL_Models.hpp>
#include <COGE/drawers_low/GL_VideoModel.hpp>

namespace COGE
{
	struct Shader3D
	{
		unsigned int projection, view, model;
		unsigned int colorConstant, colorConstant_effect;
		unsigned int xEffect, yEffect, zEffect;
		unsigned int cameraPosition;
		unsigned int sunDirection;

		void init(GLS::ShaderProgram sp);
	};

	struct ShaderUI
	{
		unsigned int screen_size, object_size, position, transform;

		void init(GLS::ShaderProgram sp);
		void setPos(glm::vec2 pos_val) { glUniform2f(position, pos_val.x, pos_val.y); }
		void setSize(glm::vec2 size_val) { glUniform2f(object_size, size_val.x, size_val.y); }
	};
}

#endif