#include <COGE/Mathematics.h>
#include <COGE/drawers_low/GL_LeCamera.hpp>

namespace GLS
{
	glm::mat4 Camera::getView()
	{
		return glm::rotate(glm::mat4(1.0f),glm::radians(-basic_rotate),glm::vec3(0.0f,0.0f,1.0f)) 
				* glm::lookAt(position, position-cameraRDirection, up);
	}

	glm::mat4 Camera::getLooking(glm::vec3 target)
	{
		return glm::lookAt(position, target, up);
	}

	void Camera::updateByTarget(glm::vec3 cameraTarget)
	{
		cameraRDirection = glm::normalize(position - cameraTarget);
		right = glm::normalize( glm::cross(glm::vec3(0.0f,1.0f,0.0f), cameraRDirection));
		up = glm::cross(cameraRDirection, right);
	}
			
	void Camera::updateByDirection(glm::vec3 cameraDirection)
	{
		cameraRDirection = -glm::normalize(cameraDirection);
		right = glm::normalize( glm::cross(glm::vec3(0.0f,1.0f,0.0f), cameraRDirection));
		up = glm::cross(cameraRDirection, right);
	}

	void Camera::transform(glm::vec3 v)
	{

	}

}