#include "blockRanderMaster.h"



blockRanderMaster::blockRanderMaster(Camera *ca)
{
	glGenBuffers(2, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //Î»ÖÃ
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //ÑÕÉ«
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);


	for (int i = 0; i < 10; i++)
	{
		Shader* myshader = new Shader("./GLSL/vertex.GLSL", "./GLSL/fragment.GLSL");
		m_shader[block_kinds[i]] = *myshader;
		camera = ca;

		glGenTextures(1, TexBuffer + i);

		glActiveTexture(GL_TEXTURE0);
		std::string file = "./Texture/blocks/" + block_kinds[i] + ".png";
		MakeTextureBuffer(TexBuffer[i], file.data());
	}

	Shader* myshader = new Shader("./GLSL/hand_vertex.GLSL", "./GLSL/hand_fragment.GLSL");
	m_shader["hand"] = *myshader;

	proMat = camera->proMat;

	std::string file = "./Texture/map/world1.png";
	MakeWorld(file.data());
	glfwSetTime(0.0);
}


blockRanderMaster::~blockRanderMaster()
{
}

void blockRanderMaster::drawHand()
{
	glm::vec3 light(1, -1, -1);
	string nowBlock = block_kinds[camera->nowblock];
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBuffer[camera->nowblock]);
	

	m_shader["hand"].use();

	GLuint ID = m_shader["hand"].getID();
	glUniform1i(glGetUniformLocation(ID, "ourTexture"), 0);
	glUniform1i(glGetUniformLocation(ID, "faceTexCoord"), 1);
	glUniform3fv(glGetUniformLocation(ID, "lightPos"), 1, glm::value_ptr(light));
	glUniform3fv(glGetUniformLocation(ID, "direction"), 1, glm::value_ptr(light));
	m_shader["hand"].setVec3("lightColor", 1.0, 1.0, 1.0);

	m_shader["hand"].setVec3("material.ambient", 0.3f, 0.3f, 0.3f);
	m_shader["hand"].setVec3("material.diffuse", 0.8f, 0.8f, 0.8f);
	m_shader["hand"].setVec3("material.specular", 0.0f, 0.0f, 0.0f);
	m_shader["hand"].setFloat("material.shininess", 32.0f);
	m_shader["hand"].setVec3("viewPos", camera->Position);


	proMat = glm::mat4(1.0f);
	viewMat = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.5f));
	model = glm::rotate(model, 45.0f, glm::vec3(-1, -1, 1));
	glUniformMatrix4fv(glGetUniformLocation(ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(glGetUniformLocation(ID, "proMat"), 1, GL_FALSE, glm::value_ptr(proMat));
	glUniformMatrix4fv(glGetUniformLocation(ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLES, 0, 36);



}

void blockRanderMaster::draw()
{

	drawHand();
	double time = glfwGetTime();
	glm::vec3 light(1, -1, -1);

	viewMat = camera->GetViewMatrix();
	proMat = camera->proMat;

	for (int i = 0; i < 10; i++)
	{
		string nowBlock = block_kinds[i];
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBuffer[i]);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_CUBE_MAP, sky);


		m_shader[nowBlock].use();
		GLuint ID = m_shader[nowBlock].getID();
		glUniform1i(glGetUniformLocation(ID, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(ID, "faceTexCoord"), 1);
		glUniform1i(glGetUniformLocation(ID, "sky"),2);

		glUniform3fv(glGetUniformLocation(ID, "lightPos"), 1, glm::value_ptr(light));
		glUniform3fv(glGetUniformLocation(ID, "direction"), 1, glm::value_ptr(light));
		m_shader[nowBlock].setVec3("lightColor", 1.0, 1.0, 1.0);
		m_shader[nowBlock].setInt("iswater", 0);
		
		m_shader[nowBlock].setFloat("time", time);

		if (i == 4)
		{
			m_shader[nowBlock].setVec3("material.ambient", 0.3f, 0.3f, 0.3f);
			m_shader[nowBlock].setVec3("material.diffuse", 0.5f, 0.0f, 0.0f);
			m_shader[nowBlock].setVec3("material.specular", 1.9f, 1.9f, 1.9f);
			m_shader[nowBlock].setFloat("material.shininess", 92.0f);
			m_shader[nowBlock].setVec3("viewPos", camera->Position);
			m_shader[nowBlock].setInt("iswater", 1);
		}
		else if (i == 3)
		{
			m_shader[nowBlock].setVec3("material.ambient", 0.1f, 0.1f, 0.1f);
			m_shader[nowBlock].setVec3("material.diffuse", 0.9f, 0.9f, 0.9f);
			m_shader[nowBlock].setVec3("material.specular", 0.0f, 0.0f, 0.0f);
			m_shader[nowBlock].setFloat("material.shininess", 32.0f);
			m_shader[nowBlock].setVec3("viewPos", camera->Position);
		}
		else
		{
			m_shader[nowBlock].setVec3("material.ambient", 0.3f, 0.3f, 0.3f);
			m_shader[nowBlock].setVec3("material.diffuse", 0.8f, 0.8f, 0.8f);
			m_shader[nowBlock].setVec3("material.specular", 0.0f, 0.0f, 0.0f);
			m_shader[nowBlock].setFloat("material.shininess", 32.0f);
			m_shader[nowBlock].setVec3("viewPos", camera->Position);
		}


		glUniformMatrix4fv(glGetUniformLocation(ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(ID, "proMat"), 1, GL_FALSE, glm::value_ptr(proMat));

		glm::vec3 pos;
		for (auto &model : m_blocks[i])
		{
			pos = glm::vec3(model[3].x, model[3].y, model[3].z);

			if (glm::distance(pos, camera->Position) > 65)
			{
				continue;
			}


			float ang = glm::dot(glm::normalize(camera->Forward), glm::normalize(pos - camera->Position));
			if (ang < 0.0)
			{
				continue;
			}

			glUniformMatrix4fv(glGetUniformLocation(ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(model));
			if (i == 4)
			{

				glDrawArrays(GL_TRIANGLES, 24, 30);
			}
			else if (i == 5 || i == 6)
			{
				glDrawArrays(GL_TRIANGLES, 12, 18);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		
		}
	}
}
