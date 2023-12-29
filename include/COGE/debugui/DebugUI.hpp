// I want to write a code that combines every text thing in a one array. one buffer.

#ifndef COGE_DEBUGUI_HPP
#define COGE_DEBUGUI_HPP

#include <iostream>

//#include <COGE/debugui/COGE_DebugUI_Letters.hpp>
#include <COGE/drawers_low/GL_Draw.hpp>
#include <COGE/renderer/StandardShaders.h>

namespace COGE
{
	GLS::Drawer* get_A();
	class Text
	{
	private:
		GLS::Drawer* text_drawer;
		float size;
		unsigned int characters = 0;
	public:
		glm::vec2 position = glm::vec3(0.0f);
		Text(std::string text, float size)
		{
			text_drawer = get_A();
			this->size = size;
			characters = text.size();
		}

		~Text()
		{
			delete text_drawer;
			text_drawer = nullptr;
		}

		void draw_test(ShaderUI UIShader_uniforms)
		{
			glm::vec2 text_size = glm::vec2(size*characters*0.4f,size);
			UIShader_uniforms.setPos(position);
			UIShader_uniforms.setSize(text_size);
			glUniformMatrix4fv(UIShader_uniforms.transform, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
			text_drawer->drawElements();
		}
	};

}

#endif