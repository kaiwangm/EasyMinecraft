#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"
#include"Shader.h"

float vertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};
// 0,1,2     2,1,3
unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 2, // 第一个三角形
	2, 3, 0  // 第二个三角形
};


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Minecraft", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "open windows filed." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "init glew filed." << std::endl;
	}

	glViewport(0, 0, 800, 600);
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/

	GLuint VAO[1];
	glGenVertexArrays(1, VAO);
	glBindVertexArray(VAO[0]);

	GLuint VBO[1];
	glGenBuffers(1, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	GLuint EBO[1];
	glGenBuffers(1, EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	Shader shaderpro("vertex.GLSL", "fragment.GLSL");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //位置
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //颜色
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); //颜色
	glEnableVertexAttribArray(2);

	GLuint TexBuffer[1];
	glGenTextures(1, TexBuffer);
	glBindTexture(GL_TEXTURE_2D, TexBuffer[0]);

	int width, height, nrchannel;
	unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrchannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "load texture failed." << std::endl;
	}
	stbi_image_free(data);

	

	while (!glfwWindowShouldClose(window))
	{ 
		processInput(window);

		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
		glBindTexture(GL_TEXTURE_2D, TexBuffer[0]);

		glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		float timevalue = glfwGetTime();
		float greenvalue = (sin(timevalue) / 2.0f) + 0.5f;
		GLuint vertexcolorcation = glGetUniformLocation(shaderpro.getID(), "ourcolor");
		shaderpro.use();
		glUniform4f(vertexcolorcation, greenvalue, greenvalue, greenvalue, 1.0f);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}