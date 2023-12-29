#include <COGE/renderer/StandardShaders.h>


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
	cameraPosition = sp.UniformLocation("cameraPosition");
	sunDirection = sp.UniformLocation("sunDirection");
}

void COGE::ShaderUI::init(GLS::ShaderProgram sp)
{
	screen_size = sp.UniformLocation("screen_size");
	object_size = sp.UniformLocation("object_size");
	position = sp.UniformLocation("position");
	transform = sp.UniformLocation("transform");
}