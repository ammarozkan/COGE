#include <COGE/renderer/General.h>


namespace COGE
{
	GeneralRenderer::GeneralRenderer()
	{
		shader = nullptr;
	}

	GeneralRenderer::~GeneralRenderer()
	{
		if(shader!=nullptr) delete shader;
	}


	void GeneralRenderer::initShader(GLS::ShaderText shader_text)
	{
		shader = new GLS::ShaderProgram(shader_text);
		uniforms.init(*shader);
	}

	void GeneralRenderer::setCamera(GLS::Camera* camera)
	{
		this->camera = camera;
	}

	void GeneralRenderer::setSky(Sky* sky)
	{
		this->sky = sky;
	}

	void GeneralRenderer::changeProjection(glm::mat4 proj)
	{
		glUniformMatrix4fv(uniforms.projection, 1, GL_FALSE, glm::value_ptr(proj));
	}

	void GeneralRenderer::use(glm::mat4 proj)
	{
		shader->use();
		glUniformMatrix4fv(uniforms.view, 1, GL_FALSE, glm::value_ptr(camera->getView()));
		changeProjection(proj);
		glUniform3f(uniforms.sunDirection, sky->sunDirection.x,sky->sunDirection.y,sky->sunDirection.z);
	}

	const Shader3D GeneralRenderer::getUniforms()
	{
		return uniforms;
	}

	void GeneralRenderer::draw(GLS::Drawer* drawer, GLS::Object3D& object)
	{
		object.modelRefresh();
		object.shader_model(uniforms.model);
		drawer->drawElements();
	}

}