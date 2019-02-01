#pragma once
#include <stdlib.h> 
#include "entity.h"
#include<iostream>
#include<vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include"../Shader.h"
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;


class blockRanderMaster
{
private:
	inline const static float vertices[288] = {
	-0.5f, -0.5f, -0.5f,  0.25f, 0.3333f,	0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.5f, 0.3333f,	0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.5f, 0.00f,      0.0f,  0.0f, -1.0f,//后
	 0.5f,  0.5f, -0.5f,  0.5f, 0.00f,		0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.00f,		0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.25f, 0.3333f,	0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.25f, 1.0f,		0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.5f, 1.0f,		0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,      0.0f,  0.0f, 1.0f,//前
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,		0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.25f, 0.66f,		0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.25f, 1.0f,		0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  0.0f, 0.66f,		1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,		1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.25f, 0.33f,     1.0f,  0.0f,  0.0f,//左
	-0.5f, -0.5f, -0.5f,  0.25f, 0.33f,		1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.33f,		1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.66f,		1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,		1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.75f, 0.66f,		1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.75f, 0.33f,		1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.75f, 0.33f,     1.0f,  0.0f,  0.0f,    //右
	 0.5f, -0.5f,  0.5f,  0.5f, 0.33f,		1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.66f,		1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 0.66f,		0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.25f, 0.66f,		0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.25f, 0.33f,     0.0f, -1.0f,  0.0f,    //底
	 0.5f, -0.5f,  0.5f,  0.25f, 0.33f,		0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.33f,		0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.66f,		0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,		0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.5f, 0.66f,      0.0f,  1.0f,  0.0f,//顶
	 0.5f,  0.5f,  0.5f,  0.5f, 0.33f,		0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.5f, 0.33f,		0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.25f, 0.33f,		0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.25f, 0.66f,		0.0f,  1.0f,  0.0f
	};
	
	string block_kinds[10] = { "gress", "brick","base","sand","water","flower","bush","tree","leaf" };
	GLuint VBO[2];
	GLuint sky;
	Camera* camera;
	glm::mat4 viewMat = glm::mat4(1.0f);
	glm::mat4 proMat = glm::mat4(1.0f);
	
	GLuint TexBuffer[10];
	time_t now_time;
	void MakeTextureBuffer(GLuint TexBuffer, const char* file)
	{

		stbi_set_flip_vertically_on_load(true);
		glBindTexture(GL_TEXTURE_2D, TexBuffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// 设置纹理
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		int width, height, nrchannel;
		unsigned char* data = stbi_load(file, &width, &height, &nrchannel, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA
				, width, height, 0, GL_RGBA
				, GL_UNSIGNED_BYTE, data);// 生成纹理
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
					int glow = data[i*width + j] /6;
					if (glow <= 3)
					{
						m_blocks[2].push_back(glm::vec3(i, 0, j));
						Has_block[{i, 0, j}] = true;
						//m_blocks[4].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, 0 + 1, j)));
						//m_blocks[4].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i, 0 + 2, j)));
						m_blocks[4].push_back(glm::vec3(i, 0 + 4, j));
						continue;
					}
					for (int k = 0; k <= glow; k++)
					{

						if (k == 0)
						{
							m_blocks[2].push_back(glm::vec3(i, k, j));
						}
						else if (k == 4)
						{
							m_blocks[3].push_back(glm::vec3(i, k, j));
						}
						else if (k == glow)
						{
							m_blocks[0].push_back( glm::vec3(i, k, j));
							if (rand() % 30 == 0 && glow >= 8)
							{
								m_blocks[5].push_back(glm::vec3(i, k + 1, j));
								Has_block[{i, k + 1, j}] = true;
							}
							else if (rand() % 8 == 1)
							{
								m_blocks[6].push_back( glm::vec3(i, k + 1, j));
								Has_block[{i, k + 1, j}] = true;
							}
							else if (rand() % 100 == 2 && glow <= 5)
							{
								for (int hei = 0; hei < 10; hei++)
								{
									m_blocks[7].push_back( glm::vec3(i, k + hei, j));
									Has_block[{i, k + hei, j}] = true;
									if (hei > 5)
									{
										for (int w = -2; w <= 2; w++)
										{
											for (int d = -2; d <= 2; d++)
											{
												m_blocks[8].push_back(glm::vec3(i + w, k + hei, j + d));
												Has_block[{i + w, k + hei, j + d}] = true;
											}
										}
									}
								}
							}
						}
						else
						{
							m_blocks[1].push_back(glm::vec3(i, k, j));
						}
						Has_block[{i, k, j}] = true;
					}

				}
			}


			for (auto iter : Has_block)
			{
				int x, y, z;
				std::tie(x, y, z) = iter.first;

				if ((Has_block.find({ x, y, z + 1 }) != Has_block.end()))
				{

				}
				else
				{
					Should_draw[{x, y, z }] = true;
					continue;
				}

				if ((Has_block.find({ x, y, z - 1 }) != Has_block.end()))
				{

				}
				else
				{
					Should_draw[{x, y, z }] = true;
					continue;
				}


				if ((Has_block.find({ x, y + 1, z }) != Has_block.end()))
				{

				}
				else
				{
					Should_draw[{x, y, z }] = true;
					continue;
				}

				if ((Has_block.find({ x, y - 1, z }) != Has_block.end()))
				{
				}
				else
				{
					Should_draw[{x, y, z }] = true;
					continue;
				}

				if ((Has_block.find({ x + 1, y, z }) != Has_block.end()))
				{

				}
				else
				{
					Should_draw[{x, y, z }] = true;
					continue;
				}

				if ((Has_block.find({ x - 1, y, z }) != Has_block.end()))
				{
				}
				else
				{
					Should_draw[{x, y, z }] = true;
					continue;
				}
			}
		}
		else
		{
			std::cout << "load texture failed." << std::endl;
		}
	}
public:
	glm::mat4 lightSpaceMatrix;
	map<string, Shader> m_shader;
	vector<glm::vec3> m_blocks[10];
	GLfloat m_invbo[10];
	map<std::tuple<int, int, int>, bool> Has_block;
	map<std::tuple<int, int, int>, bool> Should_draw;
	blockRanderMaster(Camera *ca);
	bool is_Has_Block(int i, int j, int k)
	{
		return Has_block[{i, k, j}];
	}
	~blockRanderMaster();
	void drawHand();
	void draw();
	void draw(Shader & shader);
	void setSky(GLuint k)
	{
		sky = k;
	}
};

