#include "blockRanderMaster.h"



blockRanderMaster::blockRanderMaster(Camera *ca)
{
	glGenBuffers(1, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //Î»ÖÃ
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //ÑÕÉ«
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	for (int i = 0; i < 2; i++)
	{
		Shader* myshader = new Shader("./GLSL/vertex.GLSL", "./GLSL/fragment.GLSL");
		m_shader[block_kinds[i]] = *myshader;
		camera = ca;

		glGenTextures(1, TexBuffer+i);

		glActiveTexture(GL_TEXTURE0);
		std::string file = "./Texture/blocks/" + block_kinds[i] + ".png";
		MakeTextureBuffer(TexBuffer[i], file.data());
	}
	
	proMat = camera->proMat;

	std::string file = "./Texture/map/world1.png";
	MakeWorld(file.data());

}


blockRanderMaster::~blockRanderMaster()
{
}

void blockRanderMaster::draw()
{
	glm::vec3 light(-5.0f, 5.0f, 5.0f);

	viewMat = camera->GetViewMatrix();
	proMat = camera->proMat;

	for (int i = 0; i < 3; i++)
	{
		string nowBlock = block_kinds[i];
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBuffer[i]);

		m_shader[nowBlock].use();
		GLuint ID = m_shader[nowBlock].getID();
		glUniform1i(glGetUniformLocation(ID, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(ID, "faceTexCoord"), 1);
		glUniform3fv(glGetUniformLocation(ID, "lightPos"),1, glm::value_ptr(light));

		m_shader[nowBlock].setVec3("material.ambient", 0.5f, 0.5f, 0.5f);
		m_shader[nowBlock].setVec3("material.diffuse", 0.9f, 0.9f, 0.9f);
		m_shader[nowBlock].setVec3("material.specular", 0.2f, 0.2f, 0.2f);
		m_shader[nowBlock].setFloat("material.shininess", 32.0f);
		m_shader[nowBlock].setVec3("viewPos", camera->Position);
		m_shader[nowBlock].setVec3("lightColor", 0.8f, 0.8f, 0.9f);

		glUniformMatrix4fv(glGetUniformLocation(ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(ID, "proMat"), 1, GL_FALSE, glm::value_ptr(proMat));

		for (auto model : m_blocks[i])
		{
			glUniformMatrix4fv(glGetUniformLocation(ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	
	
}
