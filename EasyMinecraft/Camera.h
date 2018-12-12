#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	void UpdateCameraVectors();
	float SensitivityX = 0.01f;
	float SensitivityY = 0.01f;
public:
	Camera(glm::vec3 position,glm::vec3 target,glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 wordlup) ;
	~Camera();

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;

	float Pitch;
	float Yaw;

	
	float speedZ = 0;
	float speedX = 0;
	float speedY = 0;

	float angle = 65.0f;
	

	glm::mat4 proMat = glm::perspective(glm::radians(65.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);
	glm::mat4 ViewMatrix = glm::mat4(1.0f);
	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(float detalX, float detalY) ;
	void UpdateCameraPosition();
	void processInput(GLFWwindow *window);
	//void mouse_callback(GLFWwindow* window, double xPos, double yPos);
};

