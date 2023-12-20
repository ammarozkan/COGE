#ifndef COGE_GENERATORS_H
#define COGE_GENERATORS_H

GLS::MODEL* PlaneModelAllocator(unsigned int x, unsigned int y)
{
	GLS::MODEL *model = new GLS::MODEL;
	model->vertice_size = sizeof(float) * 3 * x * y;
	model->indice_size = sizeof(unsigned int) * (x-1) * (y-1) * 2 * 3;

	model->vertices = (float*)malloc(model->vertice_size);
	model->indices = (unsigned int*)malloc(model->indice_size);
	return model;
}

GLS::MODEL* PlaneModelGenerator(unsigned int x, unsigned int y, GLS::MODEL* model, float (*height_function)(float, float) = nullptr)
{
	float dx = 2.0f/x, dy = 2.0f/y;

	LOG("PLANE_VERTICES");
	for(unsigned int iY = 0;iY<y;iY++)
	{
		for(unsigned int iX = 0;iX<x;iX++)
		{
			model->vertices[iY*x*3 + iX*3 + 0] = dx*iX - 1.0f;
			if(height_function!=nullptr) model->vertices[iY*x*3 + iX*3 + 1] = height_function(dx*iX - 1.0f,dy*iY - 1.0f);
			else model->vertices[iY*x*3 + iX*3 + 1] = 0.0f;
			model->vertices[iY*x*3 + iX*3 + 2] = dy*iY - 1.0f;
		}
	}

	LOG("PLANE_INDICES");
	unsigned int counter = 0;
	for(unsigned int iY = 0;iY<y-2;iY++)
	{
		for(unsigned int iX = 0;iX<x-2;iX++)
		{
			unsigned int point = iY*x + iX;
			model->indices[counter++] = point;
			model->indices[counter++] = point + 1;
			model->indices[counter++] = point + x;

			model->indices[counter++] = point + x + 1;
			model->indices[counter++] = point + 1;
			model->indices[counter++] = point + x;
		}
	}
	return model;
}

#endif