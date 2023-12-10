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
	float heightFunction(float x, float y)
	{
		float xs = automation(20,x)/10.0f;
		float ys = automation(20,y)/10.0f;
		return xs + ys - 0.5f;
	}

	GLS::Drawer* terrain;
	GAME_Terrain(int x, int y)
	{
		unsigned int vertices_size = sizeof(float) * 3 * x * y,
					indice_size = sizeof(unsigned int) * (x-1) * (y-1) * 2 * 3;

		float* vertices = (float*)malloc(vertices_size);
		unsigned int* indices = (unsigned int*)malloc(indice_size);

		float dx = 2.0f/x, dy = 2.0f/y;

		LOG("TERRAIN_VERTICES");

		for(unsigned int iY = 0;iY<y;iY++)
		{
			for(unsigned int iX = 0;iX<x;iX++)
			{
				vertices[iY*x*3 + iX*3 + 0] = dx*iX - 1.0f;
				vertices[iY*x*3 + iX*3 + 1] = heightFunction(dx*iX - 1.0f, dy*iY - 1.0f);
				vertices[iY*x*3 + iX*3 + 2] = dy*iY - 1.0f;
			}
		}


		LOG("TERRAIN_INDICES");

		unsigned int counter = 0;
		for(unsigned int iY = 0;iY<y-2;iY++)
		{
			for(unsigned int iX = 0;iX<x-2;iX++)
			{
				unsigned int point = iY*x + iX;
				indices[counter++] = point;
				indices[counter++] = point + 1;
				indices[counter++] = point + x;


				indices[counter++] = point + x + 1;
				indices[counter++] = point + 1;
				indices[counter++] = point + x;
			}
		}

		terrain = new GLS::Drawer(vertices_size, vertices,indice_size, indices,GL_STATIC_DRAW);
		terrain->scale = glm::vec3(50.0f,1.0f,50.0f);
	}

	void draw(GLS::ShaderProgram shader,unsigned int xyzEffect[3])
	{
		terrain->modelRefresh();
		terrain->shader_model(shader.model);
		glUniform3f(xyzEffect[0], 0.0f, 0.0f, 0.0f);
		glUniform3f(xyzEffect[1], 0.0f, +1.0f, -0.7f);
		glUniform3f(xyzEffect[2], 0.0f, 0.0f, 0.0f);
		glUniform3f(shader.colorConstant, 0.5f, 0.0f, 0.0f);
		glUniform1f(shader.colorConstant_effect, 0.0f);
		terrain->drawElements();
	}

	float getHeight(float x, float y)
	{
		return heightFunction(x/terrain->scale.x,y/terrain->scale.z)*terrain->scale.y + terrain->position.y;
	}
};