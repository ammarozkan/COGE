#ifndef COGE_WATER_H
#define COGE_WATER_H

struct ShaderWater
{
	unsigned int projection, view, model;
	unsigned int time;

	void init(GLS::ShaderProgram sp)
	{
		projection = sp.UniformLocation("projection");
		view = sp.UniformLocation("view");
		model = sp.UniformLocation("model");
		time = sp.UniformLocation("time");
	}
};

struct GAME_Water
{
	GLS::Drawer *drawer; GLS::Object3D object; GLS::ShaderProgram* shader;
	ShaderWater uniforms;
	GAME_Water() {}
	~GAME_Water(){ delete drawer;delete shader; }

	void init_drawer(GLS::MODEL& model,GLS::ShaderText sh) 
	{ 
		drawer = new GLS::Drawer(model,GL_STATIC_DRAW);
		shader = new GLS::ShaderProgram(sh.vertex.c_str(),sh.fragment.c_str());
		uniforms.init(*shader);
	}

	void refresh_projection(glm::mat4 proj,glm::mat4 view)
	{
		glUniformMatrix4fv(uniforms.projection, 1, GL_FALSE, glm::value_ptr(proj));
		glUniformMatrix4fv(uniforms.view, 1, GL_FALSE, glm::value_ptr(view));
	}

	void draw(float time)
	{
		glUniform1f(uniforms.time, time);
		object.modelRefresh();
		object.shader_model(uniforms.model);
		drawer->drawElements();
	}
};

#endif