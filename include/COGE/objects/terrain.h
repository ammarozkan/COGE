#ifndef COGE_TERRAIN_H
#define COGE_TERRAIN_H

#include <COGE/Macros.h>

class GAME_Terrain
{
private:
	float automation(unsigned int end,float x)
	{
		float r = 0.0f;
		for(float i = 0.25f;i<end;i+=0.25f)
		{
			r += sin(i*x)/sqrt(i);
		}
		return r;
	}
	
public:
	GLS::Drawer* terrain_drawer; GLS::Object3D terrain_object;

	GLS::MODEL* terrain_model;

	GAME_Terrain()
	{
		terrain_drawer = new GLS::Drawer();
		terrain_model = new GLS::MODEL;
	}

	~GAME_Terrain()
	{
		//delete terrain_drawer; // idk why but when I uncomment this line, terrain doesn't show up. :/

		/*free(terrain_model->vertices); free(terrain_model->indices);
		delete terrain_model;*/ // C++ is not happy with those I dont understand.
	}

	float heightFunction(float x, float y)
	{
		float xs = automation(20,x)/10.0f;
		float ys = automation(20,y)/10.0f;
		return xs + ys - 0.5f;
	}

	void generate(int x, int y)
	{
		terrain_model->vertice_size = sizeof(float) * 3 * x * y;
		terrain_model->indice_size = sizeof(unsigned int) * (x-1) * (y-1) * 2 * 3;

		terrain_model->vertices = (float*)malloc(terrain_model->vertice_size);
		terrain_model->indices = (unsigned int*)malloc(terrain_model->indice_size);

		float dx = 2.0f/x, dy = 2.0f/y;

		LOG("TERRAIN_VERTICES");

		for(unsigned int iY = 0;iY<y;iY++)
		{
			for(unsigned int iX = 0;iX<x;iX++)
			{
				terrain_model->vertices[iY*x*3 + iX*3 + 0] = dx*iX - 1.0f;
				terrain_model->vertices[iY*x*3 + iX*3 + 1] = heightFunction(dx*iX - 1.0f, dy*iY - 1.0f);
				terrain_model->vertices[iY*x*3 + iX*3 + 2] = dy*iY - 1.0f;
			}
		}


		LOG("TERRAIN_INDICES");

		unsigned int counter = 0;
		for(unsigned int iY = 0;iY<y-2;iY++)
		{
			for(unsigned int iX = 0;iX<x-2;iX++)
			{
				unsigned int point = iY*x + iX;
				terrain_model->indices[counter++] = point;
				terrain_model->indices[counter++] = point + 1;
				terrain_model->indices[counter++] = point + x;


				terrain_model->indices[counter++] = point + x + 1;
				terrain_model->indices[counter++] = point + 1;
				terrain_model->indices[counter++] = point + x;
			}
		}
		terrain_object.scale = glm::vec3(50.0f,1.0f,50.0f);
	}

	void init_drawer() 
	{ 
		terrain_drawer->init_buffers(*terrain_model, GL_STATIC_DRAW);
	}

	void draw(COGE::Shader3D shader,unsigned int xyzEffect[3])
	{
		terrain_object.modelRefresh();
		terrain_object.shader_model(shader.model);
		glUniform3f(xyzEffect[0], 0.0f, 0.0f, 0.0f);
		glUniform3f(xyzEffect[1], 0.0f, +1.0f, -0.7f);
		glUniform3f(xyzEffect[2], 0.0f, 0.0f, 0.0f);
		glUniform3f(shader.colorConstant, 0.5f, 0.0f, 0.0f);
		glUniform1f(shader.colorConstant_effect, 0.0f);
		terrain_drawer->drawElements();
	}

	float getHeight(float x, float y)
	{
		return heightFunction(x/terrain_object.scale.x,y/terrain_object.scale.z)*terrain_object.scale.y + terrain_object.position.y;
	}
};

#endif