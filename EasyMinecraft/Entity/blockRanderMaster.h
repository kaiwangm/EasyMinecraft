#pragma once
#include "entity.h"
#include<iostream>
#include<vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include"../Shader.h"

using namespace std;


class blockRanderMaster
{
private:
	inline const static float vertices[288] = {
	-0.5f, -0.5f, -0.5f,  0.25f, 0.3333f,	0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.5f, 0.3333f,	0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.5f, 0.00f,      0.0f,  0.0f, -1.0f,//ºó
	 0.5f,  0.5f, -0.5f,  0.5f, 0.00f,		0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.00f,		0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.25f, 0.3333f,	0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.25f, 1.0f,		0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.5f, 1.0f,		0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,      0.0f,  0.0f, 1.0f,//Ç°
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,		0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.25f, 0.66f,		0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.25f, 1.0f,		0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  0.0f, 0.66f,		1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,		1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.25f, 0.33f,     1.0f,  0.0f,  0.0f,//×ó
	-0.5f, -0.5f, -0.5f,  0.25f, 0.33f,		1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.33f,		1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.66f,		1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,		1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.75f, 0.66f,		1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.75f, 0.33f,		1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.75f, 0.33f,     1.0f,  0.0f,  0.0f,    //ÓÒ
	 0.5f, -0.5f,  0.5f,  0.5f, 0.33f,		1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,		1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 0.66f,		0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.25f, 0.66f,		0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.25f, 0.33f,     0.0f, -1.0f,  0.0f,    //µ×
	 0.5f, -0.5f,  0.5f,  0.25f, 0.33f,		0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.33f,		0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.66f,		0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,		0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.5f, 0.66f,      0.0f,  1.0f,  0.0f,//¶¥
	 0.5f,  0.5f,  0.5f,  0.5f, 0.33f,		0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.33f,		0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.25f, 0.33f,		0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,		0.0f,  1.0f,  0.0f
	};
	string block_kinds[10] = { "gress", "brick"};
	GLuint VBO[1];
	Camera* camera;
	glm::mat4 viewMat = glm::mat4(1.0f);
	glm::mat4 proMat = glm::mat4(1.0f);
	map<string, Shader> m_shader;
	vector<glm::mat4> m_blocks[10];
	GLuint TexBuffer[10];
	void MakeTextureBuffer(GLuint TexBuffer, const char* file)
	{

		stbi_set_flip_vertically_on_load(true);
		glBindTexture(GL_TEXTURE_2D, TexBuffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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
	void MakeWorld(const char* file)
	{
		int width, height, nrchannel;
		unsigned char* data = stbi_load(file, &width, &height, &nrchannel, 0);
		if (data)
		{
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					int glow = data[i*width + j]/20;
					for (int k = 0; k <= glow; k++)
					{
						m_blocks[0].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, k-20, j)));
						if (k != glow )
						{
							m_blocks[1].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, k - 20, j)));
						}
						Has_block[{i, k-20, j}] = true;
					}
					
				}
			}
		}
		else
		{
			std::cout << "load texture failed." << std::endl;
		}
	}
public:
	map<std::tuple<int, int, int>, bool> Has_block;
	blockRanderMaster(Camera *ca);
	bool is_Has_Block(int i,int j,int k)
	{
		return Has_block[{i, k - 20, j}];
	}
	~blockRanderMaster();
	void draw();
};

