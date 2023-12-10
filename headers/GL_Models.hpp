namespace GLS
{
	struct MODEL
	{
		float* vertices; unsigned int* indices;
		unsigned int vertice_size, indice_size;
		MODEL(unsigned int vertice_size, float*vertices, unsigned int indice_size, unsigned int* indices)
		{
			this->vertices = vertices; this->indices = indices;
			this->vertice_size = vertice_size; this->indice_size = indice_size;
		}
		MODEL(){};
	};
}