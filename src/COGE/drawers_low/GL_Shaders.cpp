#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include <COGE/drawers_low/GL_Shaders.hpp>
#include <COGE/Macros.h>

int gls_shader_success; char gls_shader_infoLog[512];

namespace GLS
{


	// SHADER DEFINITIONS



	Shader::Shader(const char * shader_code, unsigned int shader_type)
	{
		id = glCreateShader(shader_type);
		glShaderSource(id, 1, &shader_code, NULL);
		glCompileShader(id);

		
		glGetShaderiv(id, GL_COMPILE_STATUS, &gls_shader_success);
		if(!gls_shader_success)
		{
			glGetShaderInfoLog(id, 512, NULL, gls_shader_infoLog);
			WARN("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << gls_shader_infoLog);
			WARNPRINT("INCAME SHADER:" << shader_code);
		}
	}

	Shader::~Shader(){glDeleteShader(id);}

	void Shader::attachTo(unsigned int shaderProgram_id)
	{
		glAttachShader(shaderProgram_id, id);
	}



	// SHADER PROGRAM DEFINITIONS




	void ShaderProgram::info()
	{
		glGetProgramiv(id, GL_LINK_STATUS,&gls_shader_success);
		if(!gls_shader_success)
		{
			glGetProgramInfoLog(id,512,NULL,gls_shader_infoLog);
			WARN("ERROR::PROGRAM::LINKING::COMPILATION_FAILED\n" << gls_shader_infoLog);
		}
	}

	ShaderProgram::ShaderProgram(ShaderText text)
	{
		id = glCreateProgram();
		{
			GLS::Shader vertex(text.vertex.c_str(),GL_VERTEX_SHADER);
			GLS::Shader fragment(text.fragment.c_str(),GL_FRAGMENT_SHADER);
			vertex.attachTo(id); fragment.attachTo(id);
		}
		glLinkProgram(id);
		info();
	}

	void ShaderProgram::linkcodes(const char*vertex_code,const char* fragment_code)
	{
		id = glCreateProgram();
		{
			GLS::Shader vertex(vertex_code,GL_VERTEX_SHADER);
			GLS::Shader fragment(fragment_code,GL_FRAGMENT_SHADER);
			vertex.attachTo(id); fragment.attachTo(id);
		}
		glLinkProgram(id);
		info();
	}

	ShaderProgram::ShaderProgram(Shader vertex, Shader fragment)
	{
		id = glCreateProgram();
		vertex.attachTo(id); fragment.attachTo(id);
		glLinkProgram(id);
		info();
	}

	ShaderProgram::ShaderProgram(const char * vertex_code, const char * fragment_code)
	{
		linkcodes(vertex_code,fragment_code);
	}

	ShaderProgram::ShaderProgram(const char* summed_shader_path)
	{
		std::string vertex_shader_code, fragment_shader_code;
		bool appendor = false; // false means append to vertex, true means append to fragment

		std::ifstream input(summed_shader_path);
		for(std::string line;std::getline(input, line);)
		{
			if(line == "#GLSL_vertex") appendor = false;
			else if(line == "#GLSL_fragment") appendor = true;
			else
			{
				if(!appendor) vertex_shader_code+=line+"\n";
				else fragment_shader_code+=line+"\n";
			}
		}//vertex_shader_code+="\0";fragment_shader_code+="\0";


		linkcodes(vertex_shader_code.c_str(),fragment_shader_code.c_str());
	}

	void ShaderProgram::use()
	{
		glUseProgram(id);
	}

	unsigned int ShaderProgram::UniformLocation(const char* name)
	{
		return glGetUniformLocation(id,name);
	}



	// FreeFunctions

	

	ShaderProgram* cooldefinitor(const char*vertex_code, const char *fragment_code)
	{
		ShaderProgram* shaderprogram = nullptr;
		{
			Shader vertex(vertex_code,GL_VERTEX_SHADER), fragment(fragment_code,GL_FRAGMENT_SHADER);
			shaderprogram = new ShaderProgram(vertex,fragment);
		}
		return shaderprogram;
	}
}