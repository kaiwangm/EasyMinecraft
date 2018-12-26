#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#pragma once
#include <windows.h>
#include<iostream>
#include<vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Shader.h"
#include"Camera.h"
#include"Entity/blockRanderMaster.h"
#include"Model.h"

#define MAX_CHAR        128

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // 如果是第一次调用，执行初始化
						 // 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;

		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);

		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}


float skyboxVertices[] = {
	// positions          
	-1000.0f,  1000.0f, -1000.0f,
	-1000.0f, -1000.0f, -1000.0f,
	 1000.0f, -1000.0f, -1000.0f,
	 1000.0f, -1000.0f, -1000.0f,
	 1000.0f,  1000.0f, -1000.0f,
	-1000.0f,  1000.0f, -1000.0f,

	-1000.0f, -1000.0f,  1000.0f,
	-1000.0f, -1000.0f, -1000.0f,
	-1000.0f,  1000.0f, -1000.0f,
	-1000.0f,  1000.0f, -1000.0f,
	-1000.0f,  1000.0f,  1000.0f,
	-1000.0f, -1000.0f,  1000.0f,

	 1000.0f, -1000.0f, -1000.0f,
	 1000.0f, -1000.0f,  1000.0f,
	 1000.0f,  1000.0f,  1000.0f,
	 1000.0f,  1000.0f,  1000.0f,
	 1000.0f,  1000.0f, -1000.0f,
	 1000.0f, -1000.0f, -1000.0f,

	-1000.0f, -1000.0f,  1000.0f,
	-1000.0f,  1000.0f,  1000.0f,
	 1000.0f,  1000.0f,  1000.0f,
	 1000.0f,  1000.0f,  1000.0f,
	 1000.0f, -1000.0f,  1000.0f,
	-1000.0f, -1000.0f,  1000.0f,

	-1000.0f,  1000.0f, -1000.0f,
	 1000.0f,  1000.0f, -1000.0f,
	 1000.0f,  1000.0f,  1000.0f,
	 1000.0f,  1000.0f,  1000.0f,
	-1000.0f,  1000.0f,  1000.0f,
	-1000.0f,  1000.0f, -1000.0f,

	-1000.0f, -1000.0f, -1000.0f,
	-1000.0f, -1000.0f,  1000.0f,
	 1000.0f, -1000.0f, -1000.0f,
	 1000.0f, -1000.0f, -1000.0f,
	-1000.0f, -1000.0f,  1000.0f,
	 1000.0f, -1000.0f,  1000.0f
};



Camera camera(glm::vec3(0, 50, 0), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
float deltaX, deltaY;
float lastX;
float lastY;
bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse == true)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	deltaX = xPos - lastX;
	deltaY = yPos - lastY;
	lastX = xPos;
	lastY = yPos;
	camera.ProcessMouseMovement(deltaX, deltaY);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		camera.dig();
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		cout << "left" << endl;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		camera.put();
		break;
	default:
		return;
	}
	return;
}

void scroll_callback(GLFWwindow* window, double x, double y)
{
	std::cout << x << y << std::endl;
	camera.nowblock = camera.nowblock + 1;
	if (camera.nowblock >= 10)
	{
		camera.nowblock = camera.nowblock % 10;
	}
	cout << camera.nowblock << endl;
	return;
}



void MakeTextureBuffer(GLuint TexBuffer,const char* file)
{
	
	stbi_set_flip_vertically_on_load(true);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrchannel;
	unsigned char* data = stbi_load(file, &width, &height, &nrchannel, 0);
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
}


GLFWwindow* Gameinit()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Minecraft", NULL, NULL);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);



	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (window == NULL)
	{
		std::cout << "open windows filed." << std::endl;
		glfwTerminate();
		return NULL;
	}

	return window;
}

void getVBO()
{

}

unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}


int main()
{
	
	glfwInit();
	
	GLFWwindow* window = Gameinit();
	glfwMakeContextCurrent(window);


	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "init glew filed." << std::endl;
	}

	glViewport(0, 0, 1920, 1080);

	GLuint VAO[1];
	glGenVertexArrays(1, VAO);
	glBindVertexArray(VAO[0]);

	blockRanderMaster myblocks(&camera);
	camera.setWorld(&(myblocks.Has_block));
	camera.setbl(myblocks.m_blocks);
	//Shader ourShader("./GLSL/man_vertex.GLSL", "./GLSL/man_fragment.GLSL");
	//Model a("./man/nanosuit.obj");

	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	std::vector<std::string> faces
	{
		"./Texture/sky/right.jpg",
		"./Texture/sky/left.jpg",
		"./Texture/sky/top.jpg",
		"./Texture/sky/bottom.jpg",
		"./Texture/sky/front.jpg",
		"./Texture/sky/back.jpg"
	};
	unsigned int cubemapTexture = loadCubemap(faces);
	myblocks.setSky(cubemapTexture);
	Shader skyboxShader("./GLSL/sky_vertex.GLSL", "./GLSL/sky_fragment.GLSL");

	glm::mat4 modelMat = glm::mat4(1.0f);
	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = camera.GetViewMatrix();
	glm::mat4 proMat = glm::mat4(1.0f);
	proMat = camera.proMat;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	while (!glfwWindowShouldClose(window))
	{

		

		viewMat = camera.GetViewMatrix();
		proMat = camera.proMat;
		camera.processInput(window);

		glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		glBindVertexArray(VAO[0]);
		
		myblocks.draw();


		skyboxShader.use();
		// ... 设置观察和投影矩阵
		glUniform1i(glGetUniformLocation(skyboxShader.getID(), "skybox"), 0);
		glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(proMat));
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthMask(GL_LESS);


		

		
		glfwSwapBuffers(window);
		glfwPollEvents();
		camera.UpdateCameraPosition();
	}

	glfwTerminate();
	return 0;
}


