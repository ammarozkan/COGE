class GAME_Tree
{
private:
	GLS::Drawer* wood;
	GLS::Drawer* grass;
public:
	GLS::Object3D object;
	GAME_Tree(GLS::MODEL TreeGrass_model, GLS::MODEL TreeWood_model)
	{
		//grass = new GLS::Drawer(sizeof(grass_vertices),grass_vertices, sizeof(grass_indices),grass_indices,GL_STATIC_DRAW);
		grass = new GLS::Drawer(TreeGrass_model,GL_STATIC_DRAW);

		//wood = new GLS::Drawer(sizeof(wood_vertices),wood_vertices, sizeof(wood_indices),wood_indices,GL_STATIC_DRAW);
		wood = new GLS::Drawer(TreeWood_model,GL_STATIC_DRAW);

		object.scale = glm::vec3(2.0f,2.0f,2.0f);
	}

	void draw(COGE::Shader3D shader,unsigned int xyzEffect[3])
	{
		object.modelRefresh();
		object.shader_model(shader.model);
		
		glUniform3f(xyzEffect[0], 0.0f, 0.5f, 0.0f);
		glUniform3f(xyzEffect[1], 0.0f, 1.0f, 0.0f);
		glUniform3f(xyzEffect[2], 0.0f, 0.5f, 0.0f);
		grass->drawElements();

		glUniform3f(xyzEffect[0], 1.0f, 0.5f, 0.0f);
		glUniform3f(xyzEffect[1], 1.0f, 0.5f, 0.0f);
		glUniform3f(xyzEffect[2], 1.0f, 0.5f, 0.0f);
		wood->drawElements();
	}
};

#include <vector>

class GAME_Forest
{
private:
	std::vector<GAME_Tree> trees;
public:
	GAME_Forest(float tree_count, float scaleX, float scaleY, float midX, float midY, GAME_Terrain terrain,GLS::MODEL TreeGrass_model,GLS::MODEL TreeWood_model)
	{
		float dx = scaleX/sqrt(tree_count), dy = scaleY/sqrt(tree_count);
		float startX = midX - scaleX/2, startY = midY - scaleY/2;

		for(unsigned int idx = 0;idx<sqrt(tree_count);idx++)
		{
			for(unsigned int idy = 0;idy<sqrt(tree_count);idy++)
			{
				GAME_Tree tree(TreeGrass_model,TreeWood_model);
				tree.object.position = glm::vec3(startX + idx*dx,terrain.getHeight(startX + idx*dx,startY+idy*dy),startY+idy*dy);
				trees.push_back(tree);
			}
		}
	}

	void draw(COGE::Shader3D shader, unsigned int xyzEffect[3])
	{
		for(unsigned int i = 0;i<trees.size();i++)
		{
			trees[i].draw(shader, xyzEffect);
		}
	}
};