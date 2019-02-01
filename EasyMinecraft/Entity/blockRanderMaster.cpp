#include "blockRanderMaster.h"



blockRanderMaster::blockRanderMaster(Camera *ca)
{
	glGenBuffers(2, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //位置
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //颜色
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

	
	
	for (int i = 0; i < 10; i++)
	{
		unsigned int instanceVBO;
		glGenBuffers(1, &instanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		size_t len = m_blocks[i].size();
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * len, m_blocks[i].data(), GL_STREAM_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(4, 1);
		m_invbo[i] = instanceVBO;
	}
	
	
	glm::vec3 lightPos(150, 20, 150);
	float near_plane = 1.0f, far_plane = 200.0f;
	glm::mat4 lightOrthoPoojection = glm::ortho(-1000.0f, 1000.0f, -1000.0f, 1000.0f, near_plane, far_plane);

	//从光源位置的观察矩阵
	glm::mat4 lightView = glm::lookAt(lightPos, lightPos - glm::vec3(10, 10, 10),
		glm::vec3(0.0f, 1.0f, 0.0f));

	//组合成光源空间的变换矩阵
	lightSpaceMatrix = lightOrthoPoojection * lightView;

	for (int i = 0; i < 10; i++)
	{
		string nowBlock = block_kinds[i];
		Shader& nowsader = m_shader[nowBlock];
		GLint ID = nowsader.ID;
		nowsader.use();
		nowsader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
		glUniform1i(glGetUniformLocation(ID, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(ID, "faceTexCoord"), 1);
		glUniform1i(glGetUniformLocation(ID, "sky"), 2);
		glUniform1i(glGetUniformLocation(ID, "shadowMap"), 3);
		nowsader.setInt("iswater", 0);

		if (i == 4)
		{
			nowsader.setVec3("material.ambient", 0.3f, 0.3f, 0.3f);
			nowsader.setVec3("material.diffuse", 0.5f, 0.0f, 0.0f);
			nowsader.setVec3("material.specular", 1.9f, 1.9f, 1.9f);
			nowsader.setFloat("material.shininess", 92.0f);
			nowsader.setVec3("viewPos", camera->Position);
			nowsader.setInt("iswater", 1);
		}
		else if (i == 3)
		{
			nowsader.setVec3("material.ambient", 0.1f, 0.1f, 0.1f);
			nowsader.setVec3("material.diffuse", 0.9f, 0.9f, 0.9f);
			nowsader.setVec3("material.specular", 0.1f, 0.1f, 0.1f);
			nowsader.setFloat("material.shininess", 32.0f);
			nowsader.setVec3("viewPos", camera->Position);
		}
		else
		{
			nowsader.setVec3("material.ambient", 0.3f, 0.3f, 0.3f);
			nowsader.setVec3("material.diffuse", 0.8f, 0.8f, 0.8f);
			nowsader.setVec3("material.specular", 0.0f, 0.0f, 0.0f);
			nowsader.setFloat("material.shininess", 32.0f);
			nowsader.setVec3("viewPos", camera->Position);
		}

		glm::vec3 light(1, -1, -1);
		
		glUniform3fv(glGetUniformLocation(ID, "lightPos"), 1, glm::value_ptr(light));
		glUniform3fv(glGetUniformLocation(ID, "direction"), 1, glm::value_ptr(light));
		nowsader.setVec3("lightColor", 1.0, 1.0, 1.0);
	}


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


	Shader& nowsader = m_shader["hand"];
	nowsader.use();



	GLuint ID = m_shader["hand"].getID();
	glUniform1i(glGetUniformLocation(ID, "ourTexture"), 0);
	glUniform1i(glGetUniformLocation(ID, "faceTexCoord"), 1);
	glUniform3fv(glGetUniformLocation(ID, "lightPos"), 1, glm::value_ptr(light));
	glUniform3fv(glGetUniformLocation(ID, "direction"), 1, glm::value_ptr(light));
	nowsader.setVec3("lightColor", 1.0, 1.0, 1.0);

	nowsader.setVec3("material.ambient", 0.3f, 0.3f, 0.3f);
	nowsader.setVec3("material.diffuse", 0.8f, 0.8f, 0.8f);
	nowsader.setVec3("material.specular", 0.0f, 0.0f, 0.0f);
	nowsader.setFloat("material.shininess", 32.0f);
	nowsader.setVec3("viewPos", camera->Position);


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
	//drawHand();
	double time = glfwGetTime();
	

	drawHand();

	

	viewMat = camera->GetViewMatrix();
	proMat = camera->proMat;

	for (int i = 0; i < 10; i++)
	{
		string nowBlock = block_kinds[i];
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBuffer[i]);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_CUBE_MAP, sky);


		Shader& nowsader = m_shader[nowBlock];
		nowsader.use();
		GLuint ID = m_shader[nowBlock].getID();
		
		nowsader.setFloat("time", time);
		nowsader.setVec3("viewPos", camera->Position);
		glUniformMatrix4fv(glGetUniformLocation(ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(ID, "proMat"), 1, GL_FALSE, glm::value_ptr(proMat));

		size_t len = m_blocks[i].size();

		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, m_invbo[i]);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(4, 1);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, len);
	}
}


void blockRanderMaster::draw(Shader& shader)
{

	//drawHand();
	double time = glfwGetTime();

	for (int i = 0; i < 10; i++)
	{
		if (i == 5 || i == 6)
		{
			continue;
		}

		Shader& nowsader = shader;
		nowsader.use();

		size_t len = m_blocks[i].size();

		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, m_invbo[i]);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(4, 1);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, len);
	}
}