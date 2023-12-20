#ifndef COGE_GL_SIMPOBJECTS_HPP
#define COGE_GL_SIMPOBJECTS_HPP

namespace GLS
{

	// An interesting thing that provides a save point for our VBO and 
	// EBO without using the data function, again and again. its like 
	// magic. Do not do VBO and EBO again and again. Just bind the VAO
	// again. Mmmm... I should be a poetor
	class VAO
	{
	private:
		unsigned int id = 0;

	public:
		VAO();
		~VAO();
		void bind();
	};



	// A "buffer" thing that stores vertecies.
	class VBO
	{
	private:
		unsigned int id = 0;

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
		unsigned int id = 0;

	public:
		EBO();
		void bind();
		void data(unsigned int size, unsigned int*d,GLenum operation);
	};
}

#endif