#ifndef GL_SIMPOBJECTS_HPP
#define GL_SIMPOBJECTS_HPP

namespace GLS
{

	// An interesting thing that provides a save point for our VBO and 
	// EBO without using the data function, again and again. its like 
	// magic. Do not do VBO and EBO again and again. Just bind the VAO
	// again. Mmmm... I should be a poetor
	class VAO
	{
	private:
		unsigned int id;

	public:
		VAO();
		~VAO();
		void bind();
	};



	// A "buffer" thing that stores vertecies.
	class VBO
	{
	private:
		unsigned int id;

	public:
		VBO();
		~VBO();
		void bind();
		void data(unsigned int size, float*d, GLenum operation);
	};



	// An instructer that tells the order of "buffer" use.
	class EBO
	{
	private:
		unsigned int id;

	public:
		EBO();
		void bind();
		void data(unsigned int size, unsigned int*d,GLenum operation);
	};
}





namespace GLS
{
	VAO::VAO()
	{
		glGenVertexArrays(1, &id);
	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &id);
	}

	void VAO::bind()
	{
		glBindVertexArray(id);
	}



	VBO::VBO() { glGenBuffers(1,&id); }

	VBO::~VBO() { glDeleteBuffers(1,&id); }

	void VBO::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER,id);
	}

	void VBO::data(unsigned int size, float*d, GLenum operation)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, size, d, operation);
	}



	EBO::EBO()
	{
		glGenBuffers(1,&id);
	}

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

#endif