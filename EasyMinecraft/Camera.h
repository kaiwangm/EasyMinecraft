#pragma once
#include<iostream>
#include<vector>
#include<map>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
class pos
{
public:
	int x, y, z;
	pos(int i, int j, int k)
	{
		x = i; y = j; z = k;
	}
	bool operator < (const pos &o) const
	{
		return x < o.x || y < o.y || z < o.z;
	}
};

class Camera
{
private:
	map<std::tuple<int, int, int>, bool>* world;
	void UpdateCameraVectors();
	float SensitivityX = 0.01f;
	float SensitivityY = 0.01f;
	
public:
	double digtime;
	double puttime;

	vector<glm::mat4> *m_blocks;
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
	void setWorld(map<std::tuple<int, int, int>, bool>* bl)
	{
		world = bl;
	}
	void setbl(vector<glm::mat4> * b)
	{
		m_blocks = b;
	}
	void dig();
	void put();
	//void mouse_callback(GLFWwindow* window, double xPos, double yPos);
};

