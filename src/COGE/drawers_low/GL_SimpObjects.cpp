#include <GL/glew.h>

#include <COGE/drawers_low/GL_SimpObjects.hpp>

namespace GLS
{
	VAO::VAO() { glGenVertexArrays(1, &id); }

	VAO::~VAO() { glDeleteVertexArrays(1, &id); }

	void VAO::bind() { glBindVertexArray(id); }



	VBO::VBO() { glGenBuffers(1,&id); }
	VBO::~VBO() { glDeleteBuffers(1,&id); }
	void VBO::bind() { glBindBuffer(GL_ARRAY_BUFFER,id); }

	void VBO::data(unsigned int size, float*d, GLenum operation)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, size, d, operation);
	}



	EBO::EBO() { glGenBuffers(1,&id); }

	void EBO::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
	}

	void EBO::data(unsigned int size, unsigned int*d, GLenum operation)
	{
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, d, operation);
	}
}