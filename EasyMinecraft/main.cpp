#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#pragma once
#include<iostream>
#include<vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics.hpp>

//#include"stb_image.h"
#include"Shader.h"
#include"Camera.h"
#include"Entity/block.h"

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.25f, 0.3333f,
	 0.5f, -0.5f, -0.5f,  0.5f, 0.3333f,
	 0.5f,  0.5f, -0.5f,  0.5f, 0.00f, //后
	 0.5f,  0.5f, -0.5f,  0.5f, 0.00f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.00f,
	-0.5f, -0.5f, -0.5f,  0.25f, 0.3333f,

	-0.5f, -0.5f,  0.5f,  0.25f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.5f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f, //前
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,
	-0.5f,  0.5f,  0.5f,  0.25f, 0.66f,
	-0.5f, -0.5f,  0.5f,  0.25f, 1.0f,

	-0.5f,  0.5f,  0.5f,  0.0f, 0.66f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,
	-0.5f, -0.5f, -0.5f,  0.25f, 0.33f, //左
	-0.5f, -0.5f, -0.5f,  0.25f, 0.33f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.33f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.66f,

	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,
	 0.5f,  0.5f, -0.5f,  0.75f, 0.66f,
	 0.5f, -0.5f, -0.5f,  0.75f, 0.33f,
	 0.5f, -0.5f, -0.5f,  0.75f, 0.33f, //右
	 0.5f, -0.5f,  0.5f,  0.5f, 0.33f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,

	-0.5f, -0.5f, -0.5f,  0.0f, 0.66f,
	 0.5f, -0.5f, -0.5f,  0.25f, 0.66f,
	 0.5f, -0.5f,  0.5f,  0.25f, 0.33f,  //底
	 0.5f, -0.5f,  0.5f,  0.25f, 0.33f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.33f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.66f,

	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,
	 0.5f,  0.5f, -0.5f,  0.5f, 0.66f, //顶
	 0.5f,  0.5f,  0.5f,  0.5f, 0.33f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.33f,
	-0.5f,  0.5f,  0.5f,  0.25f, 0.33f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f
};

float skyboxVertices[] = {
	// positions          
	-20.0f,  20.0f, -20.0f,
	-20.0f, -20.0f, -20.0f,
	 20.0f, -20.0f, -20.0f,
	 20.0f, -20.0f, -20.0f,
	 20.0f,  20.0f, -20.0f,
	-20.0f,  20.0f, -20.0f,

	-20.0f, -20.0f,  20.0f,
	-20.0f, -20.0f, -20.0f,
	-20.0f,  20.0f, -20.0f,
	-20.0f,  20.0f, -20.0f,
	-20.0f,  20.0f,  20.0f,
	-20.0f, -20.0f,  20.0f,

	 20.0f, -20.0f, -20.0f,
	 20.0f, -20.0f,  20.0f,
	 20.0f,  20.0f,  20.0f,
	 20.0f,  20.0f,  20.0f,
	 20.0f,  20.0f, -20.0f,
	 20.0f, -20.0f, -20.0f,

	-20.0f, -20.0f,  20.0f,
	-20.0f,  20.0f,  20.0f,
	 20.0f,  20.0f,  20.0f,
	 20.0f,  20.0f,  20.0f,
	 20.0f, -20.0f,  20.0f,
	-20.0f, -20.0f,  20.0f,

	-20.0f,  20.0f, -20.0f,
	 20.0f,  20.0f, -20.0f,
	 20.0f,  20.0f,  20.0f,
	 20.0f,  20.0f,  20.0f,
	-20.0f,  20.0f,  20.0f,
	-20.0f,  20.0f, -20.0f,

	-20.0f, -20.0f, -20.0f,
	-20.0f, -20.0f,  20.0f,
	 20.0f, -20.0f, -20.0f,
	 20.0f, -20.0f, -20.0f,
	-20.0f, -20.0f,  20.0f,
	 20.0f, -20.0f,  20.0f
};



Camera camera(glm::vec3(0, 0, 5.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
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

	Shader shaderpro("./GLSL/vertex.GLSL", "./GLSL/fragment.GLSL");


	std::vector<block> blocks;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k= 0; k < 10; k++)
			{
				blocks.push_back(block(glm::vec3(i,-k-2 , j), "asdasd", &camera, &shaderpro)); 
			}
		}
	}
	


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
	Shader skyboxShader("./GLSL/sky_vertex.GLSL", "./GLSL/sky_fragment.GLSL");

	glm::mat4 modelMat = glm::mat4(1.0f);
	//modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0));
	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = camera.GetViewMatrix();
	glm::mat4 proMat = glm::mat4(1.0f);
	proMat = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);

	
	while (!glfwWindowShouldClose(window))
	{

		viewMat = camera.GetViewMatrix();

		camera.processInput(window);

		glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		glBindVertexArray(VAO[0]);


		
		for (auto bl : blocks)
		{
			bl.Draw();
		}
		
		

		glDepthFunc(GL_LEQUAL);
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


