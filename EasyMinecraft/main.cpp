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



Camera camera(glm::vec3(75, 15, 75), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
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



void MakeTextureBuffer(GLuint TexBuffer, const char* file)
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

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "2017192047_WangKai_project", NULL, NULL);
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


class Cloud
{
private:
	inline const static float vertices[288] = {
	-0.5f, -0.5f, -0.5f,  0.25f, 0.3333f,	0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.5f, 0.3333f,	0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.5f, 0.00f,      0.0f,  0.0f, -1.0f,//??
	 0.5f,  0.5f, -0.5f,  0.5f, 0.00f,		0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.00f,		0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.25f, 0.3333f,	0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.25f, 1.0f,		0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.5f, 1.0f,		0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,      0.0f,  0.0f, 1.0f,//?
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,		0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.25f, 0.66f,		0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.25f, 1.0f,		0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  0.0f, 0.66f,		1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,		1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.25f, 0.33f,     1.0f,  0.0f,  0.0f,//??
	-0.5f, -0.5f, -0.5f,  0.25f, 0.33f,		1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.33f,		1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.66f,		1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,		1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.75f, 0.66f,		1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.75f, 0.33f,		1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.75f, 0.33f,     1.0f,  0.0f,  0.0f,    //??
	 0.5f, -0.5f,  0.5f,  0.5f, 0.33f,		1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,		1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 0.66f,		0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.25f, 0.66f,		0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.25f, 0.33f,     0.0f, -1.0f,  0.0f,    //??
	 0.5f, -0.5f,  0.5f,  0.25f, 0.33f,		0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.33f,		0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.66f,		0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,		0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.5f, 0.66f,      0.0f,  1.0f,  0.0f,//??
	 0.5f,  0.5f,  0.5f,  0.5f, 0.33f,		0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.33f,		0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.25f, 0.33f,		0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,		0.0f,  1.0f,  0.0f
	};
	GLuint VBO[2];

public:
	vector<Cloud*> child;
	float time = 0;
	glm::mat4 tran = glm::mat4(1.0f);
	glm::mat4 rote = glm::mat4(1.0f);
	glm::mat4 scel = glm::mat4(1.0f);
	Shader cloudshader;
	void draw(glm::mat4 mod)
	{
		rote = rote * glm::rotate(glm::mat4(1.0f), 0.003f, glm::vec3(0, 1.0f, 0));
		cloudshader.use();
		cloudshader.setMat4("modelMat", tran*mod* rote*scel);
		cloudshader.setMat4("viewMat", camera.GetViewMatrix());
		cloudshader.setMat4("proMat", camera.proMat);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		for (int i = 0; i < child.size(); i++)
		{
			child[i]->draw(tran*mod);
		}
	}
	Cloud(Shader& sh)
	{
		cloudshader = sh;

		tran = glm::mat4(1.0f)*glm::translate(glm::mat4(1.0f), glm::vec3(75, 75, 75));
		scel = glm::mat4(1.0f)*glm::scale(glm::mat4(1.0f), glm::vec3(40, 7, 60));

		using namespace glm;

		for (int i = 20; i < 1000; i = i + 20)
		{
			for (int j = 20; j < 1000; j = j + 20)
			{
				child.push_back(new Cloud(sh, vec3(i * 5 + rand() % 200 - 300, rand() % 20, j * 4 + rand() % 200 - 300), 0, glm::vec3(5 + rand() % 20, 2 + rand() % 5, 5 + rand() % 20)));
			}
		}

	};

	Cloud(Shader& sh, glm::vec3 tr, float ro, glm::vec3 sc)
	{
		cloudshader = sh;

		tran = glm::mat4(1.0f)*glm::translate(glm::mat4(1.0f), tr);
		rote = glm::mat4(1.0f)*glm::rotate(glm::mat4(1.0f), ro, glm::vec3(0.0f, 1.0f, 0.0f));
		scel = glm::mat4(1.0f)*glm::scale(glm::mat4(1.0f), sc);

	};
	void settime(float time)
	{
		time = glfwGetTime();
		tran = tran * glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.1));
	}

	~Cloud() {};
};

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
	camera.setibo(myblocks.m_invbo);
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
	Shader cloudshader("./GLSL/cloud_v.glsl", "./GLSL/cloud_f.glsl");
	Cloud myc(cloudshader);
	Shader skyboxShader("./GLSL/sky_vertex.GLSL", "./GLSL/sky_fragment.GLSL");
	Shader shadowShader("./GLSL/vertex_simpleDepthShader.GLSL", "./GLSL/fragment_simpleDepthShader.GLSL");
	glm::mat4 modelMat = glm::mat4(1.0f);
	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = camera.GetViewMatrix();
	glm::mat4 proMat = glm::mat4(1.0f);
	proMat = camera.proMat;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	/** ???? */
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);

	//???2D???????????????????
	const unsigned int SHADOW_WIDTH = 9192, SHADOW_HEIGHT = 9192;
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH,
		SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//???????????????????
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);		//????OpenGL????????????????
	glReadBuffer(GL_NONE);		//????OpenGL????????????????
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	/******************************************************************/
		//???????????????????
	glm::vec3 lightPos(150, 20, 150);
	float near_plane = 1.0f, far_plane = 200.0f;
	glm::mat4 lightOrthoPoojection = glm::ortho(-1000.0f, 1000.0f, -1000.0f, 1000.0f, near_plane, far_plane);

	//??????????????
	glm::mat4 lightView = glm::lookAt(lightPos, lightPos - glm::vec3(10, 10, 10),
		glm::vec3(0.0f, 1.0f, 0.0f));

	//????????????????
	glm::mat4 lightSpaceMatrix = lightOrthoPoojection * lightView;

	//????????????
	shadowShader.use();
	shadowShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);




	while (!glfwWindowShouldClose(window))
	{



		viewMat = camera.GetViewMatrix();
		proMat = camera.proMat;
		camera.processInput(window);

		glBindVertexArray(VAO[0]);
		glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glCullFace(GL_FRONT);


		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		myblocks.draw(shadowShader);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//???????
		glViewport(0, 0, 1920, 1080);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glCullFace(GL_BACK);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		myblocks.draw();

		cout << glfwGetTime() << endl;
		myc.settime(glfwGetTime());
		myc.draw(glm::mat4(1.0f));

		skyboxShader.use();
		// ... ??????????????
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


