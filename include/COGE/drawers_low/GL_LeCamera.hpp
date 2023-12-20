#ifndef COGE_GL_LECAMERA_HPP
#define COGE_GL_LECAMERA_HPP

#include <COGE/Mathematics.h>

namespace GLS
{
	struct Camera
	{
		glm::mat4 projection;
		glm::vec3 position;
		glm::vec3 front, up, right;
		glm::vec3 cameraRDirection;
		float basic_rotate = 0.0f;

		glm::mat4 getView();
		glm::mat4 getLooking(glm::vec3 target);
		void updateByTarget(glm::vec3 cameraTarget);
		void updateByDirection(glm::vec3 cameraDirection);
		void transform(glm::vec3 v);
	};
}

#endif