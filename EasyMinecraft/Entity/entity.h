#pragma once
#include<iostream>
#include<vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics.hpp>

#include"../stb_image.h"
#include"../Shader.h"
#include"../Camera.h"
class entity
{

protected:
	glm::vec3 Position;
	std::string name;
	GLuint ID;
public:
	void MakeTextureBuffer(GLuint TexBuffer, const char* file);
	entity();
	~entity();
};

