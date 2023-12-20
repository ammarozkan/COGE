#ifndef COGE_GL_SHADERS_HPP
#define COGE_GL_SHADERS_HPP

#include <iostream>
#include <fstream>

namespace GLS
{
	struct ShaderText
	{
		std::string vertex,fragment;
	};

	class Shader
	{
	private:
		unsigned int id;
	public:
		Shader(std::string shader_path, unsigned int shader_type);
		Shader(const char *shader_code, unsigned int shader_type);
		~Shader();

		void attachTo(unsigned int shaderProgram_id);
	};
	class ShaderProgram
	{
	private:
		unsigned int id;
		void info();
		void linkcodes(const char*vertex_code,const char* fragment_code);
	public:
		ShaderProgram(ShaderText text);
		ShaderProgram(Shader vertex, Shader fragment);
		ShaderProgram(const char *vertex_code,const char *fragment_code);
		ShaderProgram(const char* summed_shader_path);
		void use();

		void initGenericUniforms();
		unsigned int UniformLocation(const char* n);
	};

	ShaderProgram* cooldefinitor(const char*vertex_code, const char *fragment_code);

	// struct Shader3D; // i'll have to use it somepoint
}

#endif