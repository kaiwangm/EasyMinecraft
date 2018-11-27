#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
	
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void use();
	GLuint getID();
private:
	std::string vertexString;
	std::string fragmentString;
	const char* vertexScource;
	const char* fragmentScource;
	GLuint ID; //shader program id	
	void checkCompileErrors(GLuint ID, std::string type);
};

