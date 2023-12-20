#ifndef COGE_GL_MODELS_HPP
#define COGE_GL_MODELS_HPP

namespace GLS
{
	struct MODEL
	{
		float* vertices; unsigned int* indices;
		unsigned int vertice_size, indice_size;
		MODEL(unsigned int vertice_size, float*vertices, unsigned int indice_size, unsigned int* indices);
		MODEL();
		~MODEL();
	};
}

#endif