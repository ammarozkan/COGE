#ifndef COGE_STATIC_MODELS_H
#define COGE_STATIC_MODELS_H

namespace COGE
{
	GLS::MODEL MODEL_Plane()
	{
		GLS::MODEL model;

		model.vertice_size = sizeof(float)*18;
		model.indice_size = sizeof(unsigned int)*27;
		model.vertices = (float*)malloc(model.vertice_size);
		model.indices = (unsigned int*)malloc(model.indice_size);

		float vertices[] = {
			0,	 0,	-1,
			0,	 0,	+1,
			-1,	 0,	-0.5,
			0,	-0.5,	-0.5,
			1,	 0,	-0.5,
			0,	 0.5,	-0.5
		};

		for(unsigned int i = 0;i<sizeof(vertices)/sizeof(float);i++) model.vertices[i] = vertices[i];

		float indices[] = {
			0,2,5,
			0,5,4,
			0,3,4,
			0,3,2,
			1,5,4,
			1,4,3,
			1,2,5,
			1,2,3,
			1,4,3
		};

		for(unsigned int i = 0;i<sizeof(indices)/sizeof(float);i++) model.indices[i] = indices[i];


		return model;
	}

	GLS::MODEL MODEL_TreeGrass()
	{
		GLS::MODEL model;

		float grass_vertices[] = 
		{
			+0.0f,	+1.0f,	+0.0f,	//0, top dot

			+0.0f, 	+0.3f,	-0.5f,	//1
			+0.5f, 	+0.3f,	+0.25f,	//2
			-0.5f, 	+0.3f,	+0.25f	//3
		};

		unsigned int grass_indices[] = 
		{
			0,	2,	3,
			0,	2,	1,
			0,	1,	3,
			1,	2,	3
		};

		model.vertice_size = sizeof(grass_vertices);
		model.indice_size = sizeof(grass_indices);
		model.vertices = (float*)malloc(model.vertice_size);
		model.indices = (unsigned int*)malloc(model.indice_size);

		memcpy(model.vertices, grass_vertices, model.vertice_size);
		memcpy(model.indices, grass_indices, model.indice_size);

		return model;
	}

	GLS::MODEL MODEL_TreeWood()
	{
		GLS::MODEL model;

		float wood_vertices[] = 
		{
			+0.0f, 	+0.3f,	-0.10f,	//0 //4 469 -> 025
			+0.1f, 	+0.3f,	+0.05f,	//1 //5 467 -> 023
			-0.1f, 	+0.3f,	+0.05f,	//2 //6

			+0.0f, 	+0.0f,	-0.10f,	//3 //7
			+0.1f, 	+0.0f,	+0.05f,	//4 //8
			-0.1f, 	+0.0f,	+0.05f	//5 //9
		};

		unsigned int wood_indices[] =
		{
			0,1,2,
			3,4,5,

			2,4,5,
			2,4,1,

			0,1,4,
			0,3,4,

			0,2,5,
			0,3,5
		};

		model.vertice_size = sizeof(wood_vertices);
		model.indice_size = sizeof(wood_indices);
		model.vertices = (float*)malloc(model.vertice_size);
		model.indices = (unsigned int*)malloc(model.indice_size);

		memcpy(model.vertices, wood_vertices, model.vertice_size);
		memcpy(model.indices, wood_indices, model.indice_size);

		return model;
	}
}

#endif