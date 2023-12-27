#include <COGE/drawers_low/GL_Models.hpp>
#include <COGE/Macros.h>
#include <cstdlib>
#include <cstring>

namespace GLS
{
	MODEL::MODEL(unsigned int vertice_size, float*vertices, unsigned int indice_size, unsigned int* indices)
	{
		this->vertice_size = vertice_size; this->indice_size = indice_size;

		this->vertices = (float*)malloc(this->vertice_size);
		this->indices = (unsigned int*)malloc(this->indice_size);

		memcpy(this->vertices, vertices, this->vertice_size);
		memcpy(this->indices, indices, this->indice_size);
	}

	MODEL::MODEL()
	{
		this->vertices = nullptr;
		this->indices = nullptr;
	}

	MODEL::~MODEL()
	{
		LOG("MODEL IS DELETENING");
		if(this->vertices != nullptr) free(this->vertices);
		if(this->indices != nullptr) free(this->indices);
	}
}