#include <COGE/drawers_low/GL_Draw.hpp>
#include <COGE/drawers_low/GL_Shaders.hpp>
#include <COGE/renderer/Sky.h>
#include <COGE/Mathematics.h>
#include <COGE/renderer/StandardShaders.h>

namespace COGE
{
	struct Material
	{
		// there will be some texture definitions.
	};
	
	class GeneralRenderer
	{
	private:
		GLS::ShaderProgram* shader; Shader3D uniforms;
		GLS::Camera* camera; Sky* sky;
		glm::mat4 cameraView;
	public:
		GeneralRenderer();
		~GeneralRenderer();
		void initShader(GLS::ShaderText);
		void setCamera(GLS::Camera*);
		void setSky(Sky*);

		const Shader3D getUniforms();

		void changeProjection(glm::mat4 proj);
		void use(glm::mat4 proj);
		void draw(GLS::Drawer* drawer, GLS::Object3D& object);
		//void setEverything(GLS::Camera*,Sky*);
	};

}