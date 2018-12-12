#pragma once
#include "entity.h"
#include<iostream>
#include<vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include"../Shader.h"

class block :
	public entity
{
private:
	inline const static float vertices[180] = {
	-0.5f, -0.5f, -0.5f,  0.25f, 0.3333f,
	 0.5f, -0.5f, -0.5f,  0.5f, 0.3333f,
	 0.5f,  0.5f, -0.5f,  0.5f, 0.00f, //ºó
	 0.5f,  0.5f, -0.5f,  0.5f, 0.00f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.00f,
	-0.5f, -0.5f, -0.5f,  0.25f, 0.3333f,

	-0.5f, -0.5f,  0.5f,  0.25f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.5f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f, //Ç°
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,
	-0.5f,  0.5f,  0.5f,  0.25f, 0.66f,
	-0.5f, -0.5f,  0.5f,  0.25f, 1.0f,

	-0.5f,  0.5f,  0.5f,  0.0f, 0.66f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,
	-0.5f, -0.5f, -0.5f,  0.25f, 0.33f, //×ó
	-0.5f, -0.5f, -0.5f,  0.25f, 0.33f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.33f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.66f,

	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,
	 0.5f,  0.5f, -0.5f,  0.75f, 0.66f,
	 0.5f, -0.5f, -0.5f,  0.75f, 0.33f,
	 0.5f, -0.5f, -0.5f,  0.75f, 0.33f, //ÓÒ
	 0.5f, -0.5f,  0.5f,  0.5f, 0.33f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,

	-0.5f, -0.5f, -0.5f,  0.0f, 0.66f,
	 0.5f, -0.5f, -0.5f,  0.25f, 0.66f,
	 0.5f, -0.5f,  0.5f,  0.25f, 0.33f,  //µ×
	 0.5f, -0.5f,  0.5f,  0.25f, 0.33f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.33f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.66f,

	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,
	 0.5f,  0.5f, -0.5f,  0.5f, 0.66f, //¶¥
	 0.5f,  0.5f,  0.5f,  0.5f, 0.33f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.33f,
	-0.5f,  0.5f,  0.5f,  0.25f, 0.33f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f
	};
	GLuint VBO[1];
	GLuint TexBuffer[2];
	Camera* camera;
	glm::mat4 viewMat = glm::mat4(1.0f);
	glm::mat4 proMat = glm::mat4(1.0f);
	glm::mat4 modelMat = glm::mat4(1.0f);

public:
	block();
	Shader* shader;
	void init();
	void Draw();
	block(glm::vec3 pos, std::string name, Camera* ca, Shader* sha);
	~block();
};

