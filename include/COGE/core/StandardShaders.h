#ifndef COGE_STANDARDSHADERS_H
#define COGE_STANDARDSHADERS_H

namespace COGE
{
	struct Shader3D
	{
		unsigned int projection, view, model;
		unsigned int colorConstant, colorConstant_effect;
		unsigned int xEffect, yEffect, zEffect;

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


void COGE::Shader3D::init(GLS::ShaderProgram sp)
{
	view = sp.UniformLocation("view");
	model = sp.UniformLocation("model");
	projection = sp.UniformLocation("projection");
	colorConstant = sp.UniformLocation("colorConstant");
	colorConstant_effect = sp.UniformLocation("colorConstant_effect");
	xEffect = sp.UniformLocation("xEffect");
	yEffect = sp.UniformLocation("yEffect");
	zEffect = sp.UniformLocation("zEffect");
}

void COGE::ShaderUI::init(GLS::ShaderProgram sp)
{
	screen_size = sp.UniformLocation("screen_size");
	object_size = sp.UniformLocation("object_size");
	position = sp.UniformLocation("position");
	transform = sp.UniformLocation("transform");
}

#endif