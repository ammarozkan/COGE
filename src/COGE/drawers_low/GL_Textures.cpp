#include <COGE/drawers_low/GL_Textures.hpp>
#include <GL/glew.h>

#include <COGE/Macros.h>

#define WHYTHFISTHISZERO 0

namespace GLS
{
	void TextureData::destroyData()
	{
		if(data!=nullptr) free(data);
	}

	Texture::Texture(TextureData td)
	{
		if(td.data == nullptr)
		{
			WARN("Texture Creation Error:DATA IS EMPTY");
			return;
		}

		texture = 0;
		glGenTextures(1,&texture);
		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLint mipmapLevel = 0;
		glTexImage2D(GL_TEXTURE_2D, mipmapLevel, GL_RGB, td.width, td.height, WHYTHFISTHISZERO, GL_RGB8, GL_UNSIGNED_BYTE, td.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture::~Texture()
	{
		unsigned int textures[] = {texture};
		glDeleteTextures(1, textures);
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	bool Texture::isOK()
	{
		return texture!=0;
	}
}