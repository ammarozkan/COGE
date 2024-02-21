#ifndef COGE_EDITOR_H
#define COGE_EDITOR_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <COGE/datas/DataLoader.hpp>
#include <COGE/datas/DataPacker.hpp>
#include <COGE/renderer/General.h>
#include <COGE/Mathematics.h>
#include <COGE/drawers_low/GL_Shaders.hpp>
#include <COGE/drawers_low/GL_Models.hpp>
#include <COGE/drawers_low/GL_VideoModel.hpp>

#include <COGE/editor/EditorCommandExecuter.h>

namespace COGE
{

	class Editor
	{
	private:
		GLFWwindow* window;

		DataLoader data_loader;
		GeneralRenderer generalRenderer; Sky sky;
		GLS::Camera camera; glm::mat4 full_projection;
		GLS::ShaderProgram *UIShader; ShaderUI UIShader_uniforms;
		GLS::MODEL* model; GLS::VideoModel* target;
		GLS::Object3D obj;
		EditorCommandExecuter ECE;

		float seeDistance = 5.0f;

		bool init_complete = false;

		float preTime;
	public:
		Editor(GLFWwindow* window);
		Editor();

		void ChangeModel(GLS::MODEL& model);
		void ChangeModel(std::string name);

		void HandleCommand(std::string);

		void Controls(float deltaTime);

		void OncePrint(float deltaTime);
		void Draw_UI();
		void inLoop(float deltaTime);
		void Work();

		~Editor();

		friend class EditorCommandExecuter;
	};
}

#endif