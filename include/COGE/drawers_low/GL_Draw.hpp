#ifndef COGE_GL_DRAW_HPP
#define COGE_GL_DRAW_HPP

#include <vector>
#include <COGE/drawers_low/GL_SimpObjects.hpp>
#include <COGE/drawers_low/GL_Models.hpp>
#include <COGE/drawers_low/GL_LeCamera.hpp>
#include <COGE/Mathematics.h>

namespace GLS
{
	struct Object3D
	{
		glm::vec3 position = glm::vec3(0);
		glm::vec3 scale = glm::vec3(1);
		glm::mat4 rotation = glm::mat4(1);
		glm::mat4 model;

		void modelRefresh();
		void shader_model(unsigned int model_location);
		void rotateRelative(glm::vec3 t, float angle);
		glm::vec3 getFront();
		glm::vec3 getRight();
	};

	class Drawer
	{
	private:
		VAO *vao = nullptr;
		VBO *vbo = nullptr;
		EBO *ebo = nullptr;
		unsigned int indices;

		void object_init(unsigned int vs, float*v, unsigned int is, unsigned int*i, unsigned int t);
	public:
		Drawer();
		Drawer(MODEL& model, unsigned int draw_type);
		Drawer(MODEL& model, unsigned int draw_type, unsigned int each_size_size, unsigned int* each_size, unsigned int sumofthem);
		~Drawer();

		void init_buffers(MODEL& model, unsigned int draw_type);
		void init_buffers(MODEL& model, unsigned int draw_type, unsigned int each_size_size, unsigned int* each_size, unsigned int sumofthem);
		
		void drawTriangle();
		void drawElements();
	};
}
#endif