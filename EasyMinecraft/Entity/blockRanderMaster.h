#pragma once
#include <stdlib.h> 
#include "entity.h"
#include<iostream>
#include<vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include"../Shader.h"
#include <ctime>

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
	string block_kinds[10] = { "gress", "brick","base","sand","water","flower","bush" };
	GLuint VBO[1];
	Camera* camera;
	glm::mat4 viewMat = glm::mat4(1.0f);
	glm::mat4 proMat = glm::mat4(1.0f);
	map<string, Shader> m_shader;
	GLuint TexBuffer[10];
	time_t now_time;
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
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
					int glow = data[i*width + j] / 10;
					if (glow <= 3)
					{
						m_blocks[2].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, 0, j)));
						Has_block[{i, 0, j}] = true;
						//m_blocks[4].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, 0 + 1, j)));
						//m_blocks[4].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, 0 + 2, j)));
						m_blocks[4].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, 0 + 4, j)));
						continue;
					}
					for (int k = 0; k <= glow; k++)
					{

						if (k == 0)
						{
							m_blocks[2].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, k, j)));
						}
						else if (k == 4)
						{
							m_blocks[3].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, k, j)));
						}
						else if (k == glow)
						{
							m_blocks[0].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, k, j)));
							if (rand() % 30 == 0 && glow >= 8)
							{
								m_blocks[5].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, k + 1, j)));
							}
							else if (rand() % 8 == 1)
							{
								m_blocks[6].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, k + 1, j)));
							}
						}
						else
						{
							m_blocks[1].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, k, j)));
						}
						Has_block[{i, k, j}] = true;
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
	vector<glm::mat4> m_blocks[10];
	map<std::tuple<int, int, int>, bool> Has_block;
	blockRanderMaster(Camera *ca);
	bool is_Has_Block(int i, int j, int k)
	{
		return Has_block[{i, k, j}];
	}
	~blockRanderMaster();
	void draw();
};

