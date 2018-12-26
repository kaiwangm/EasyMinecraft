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
	if (Pitch - deltaY * SensitivityX<1.5&&Pitch - deltaY * SensitivityX > -1.5)
		Pitch -= deltaY * SensitivityX;
	Yaw -= deltaX * SensitivityY;
	UpdateCameraVectors();
}

void Camera::UpdateCameraPosition()
{
	/*Position += Forward * speedZ;
	Position += -Right * speedX;
	Position += -Up*speedY;*/
	glm::vec3  Positiondeta = glm::vec3(1, 0, 1)*Forward * speedZ - glm::vec3(1, 0, 1)*Right * speedX - glm::vec3(0, 1, 0)*Up*speedY;
	glm::vec3  judePosition = Position + glm::vec3(10.0f)* Positiondeta;
	glm::vec3 nextPosition = Position + Positiondeta;

	int x = judePosition.x, y = judePosition.y, z = judePosition.z;
	if (!(*world)[{x, y, z }])
	{
		Position = nextPosition;
	}
	else
	{
		if ((speedX > 0.1 || speedZ > 0.1))
		{
			//speedX = 0;
			speedY = 0.1f;
			//speedZ = 0;
			Position.y += 0.1;
		}

	}


	ViewMatrix = glm::lookAt(Position, Position + Forward, WorldUp);
	proMat = glm::perspective(glm::radians(angle), 1920.0f / 1080.0f, 0.01f, 3000.0f);
}

void Camera::dig()
{
	glm::vec3  Positiondeta = glm::vec3(1, 1, 1)*Forward;
	glm::vec3  judePosition = Position + Positiondeta;

	if (glfwGetTime() - digtime < 0.05)
	{
		return;
	}
	for (int t = 0; t < 15; t++)
	{
		int x = judePosition.x, y = judePosition.y, z = judePosition.z;
		if ((*world)[{x, y, z }])
		{
			(*world)[{x, y, z }] = false;


			glm::vec3 compare = glm::vec3(x, y, z);
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < m_blocks[i].size(); j++)
				{
					if (m_blocks[i][j] == compare)
					{
						std::cout << "dig" << std::endl;
						m_blocks[i].erase(m_blocks[i].cbegin() + j);
						digtime = glfwGetTime();
						return;
					}
				}
			}
		}
		judePosition += Positiondeta;
	}

}


void Camera::put()
{
	glm::vec3  Positiondeta = glm::vec3(1, 1, 1)*Forward;
	glm::vec3  judePosition = Position + Positiondeta;

	if (glfwGetTime() - puttime < 0.3)
	{
		return;
	}

	for (int t = 0; t < 15; t++)
	{
		int x = judePosition.x, y = judePosition.y, z = judePosition.z;
		if ((*world)[{x, y, z }])
		{
			if (!(*world)[{x, y + 1, z }])
			{
				std::cout << "put" << std::endl;
				m_blocks[nowblock].push_back(glm::vec3(x, y + 1, z));
				(*world)[{x, y + 1, z}] = true;
				puttime = glfwGetTime();
				return;
			}

		}
		judePosition += Positiondeta;
	}

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

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			if (angle <= 145.0f)
			{
				speedZ = 0.2f;
				angle = angle * 1.03;
			}
	}
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		dig();
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		put();
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
		return;
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

	if (!(*world)[{Position.x, Position.y - 1, Position.z}])
	{
		speedY -= 0.005f;
	}
	else
	{
		speedY = 0;
	}
}



