namespace GLS
{
	struct Camera
	{
		glm::mat4 projection;
		glm::vec3 position;
		glm::vec3 front, up, right;
		glm::vec3 cameraRDirection;
		float basic_rotate = 0.0f;

		glm::mat4 getView()
		{
			return glm::rotate(glm::mat4(1.0f),glm::radians(-basic_rotate),glm::vec3(0.0f,0.0f,1.0f)) * glm::lookAt(position, position-cameraRDirection, up);
		}

		glm::mat4 getLooking(glm::vec3 target)
		{
			return glm::lookAt(position, target, up);
		}

		void updateByTarget(glm::vec3 cameraTarget)
		{
			cameraRDirection = glm::normalize(position - cameraTarget);
			right = glm::normalize( glm::cross(glm::vec3(0.0f,1.0f,0.0f), cameraRDirection));
			up = glm::cross(cameraRDirection, right);
		}
		
		void updateByDirection(glm::vec3 cameraDirection)
		{
			cameraRDirection = -glm::normalize(cameraDirection);
			right = glm::normalize( glm::cross(glm::vec3(0.0f,1.0f,0.0f), cameraRDirection));
			up = glm::cross(cameraRDirection, right);
		}

		void transform(glm::vec3 v)
		{

		}
	};
}
