#include "Camera.h"

void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));

}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 wordlup)
{
	Position = position;
	WorldUp = wordlup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(pitch)*glm::sin(yaw);
	Forward.y = glm::sin(pitch);
	Forward.z = glm::cos(pitch)*glm::cos(yaw);

}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	return ViewMatrix;
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	Pitch -= deltaY * SensitivityX;
	Yaw -= deltaX * SensitivityY;
	UpdateCameraVectors();
}

void Camera::UpdateCameraPosition()
{
	/*Position += Forward * speedZ;
	Position += -Right * speedX;
	Position += -Up*speedY;*/

	Position += glm::vec3(1, 0, 1)*Forward * speedZ;
	Position += -glm::vec3(1, 0, 1)*Right * speedX;
	Position += -glm::vec3(0, 1, 0)*Up*speedY;
	ViewMatrix = glm::lookAt(Position, Position + Forward, WorldUp);
	proMat = glm::perspective(glm::radians(angle), 1920.0f / 1080.0f, 0.1f, 1000.0f);
}




void Camera::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		speedZ = 0.1f;
		if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		if (angle <= 145.0f)
		{
			speedZ = 0.2f;
			angle = angle * 1.03;
		}
		
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		speedZ = -0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		speedX = 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		speedX = -0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		speedY = 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		speedY = -0.1f;
	}
	else
	{
		speedZ *= 0.95f;
		speedX *= 0.95f;
		angle = 65.0f + (angle - 65.0f)*0.95f;
	}
	
	if (Position.y > -1||speedY==0.1f)
	{
		speedY -= 0.005f;
	}
	else if((Position.y <= -1))
	{
		speedY = 0;
	}
}



