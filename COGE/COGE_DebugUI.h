// I want to write a code that combines every text thing in a one array. one buffer.

#include "DebugUI/COGE_DebugUI_Letters.h"

namespace COGE
{
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

		void draw_test(GLS::ShaderProgram UIShader)
		{
			glm::vec2 text_size = glm::vec2(size*characters*0.4f,size);
			text_drawer->drawElements();
			glUniformMatrix4fv(UIShader.model, 1, GL_FALSE, glm::value_ptr(glm::scale(glm::mat4(1.0f),glm::vec3(size*0.4,size,1.0f))));
			glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3(position.x+text_size.x/2,position.y+text_size.y/2,0.0f));
			glUniformMatrix4fv(UIShader.view, 1, GL_FALSE, glm::value_ptr(view));
		}
	};

	class DUI
	{

	};
}