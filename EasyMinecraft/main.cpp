#define GLEW_STATIC
#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //0
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,//1
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,//2
	 0.8f,  0.8f, 0.0f, 0.7f, 0.3f, 0.6f, 1.0f,//3
};
// 0,1,2     2,1,3
unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 2, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

const GLchar* vShaderSrc = "#version 330 core               \n"
"layout(location = 0) in vec3 aPos;           \n"
"layout(location = 1) in vec4 acolor;           \n"
"out vec4 vertexcolor;            \n"
"void main(){                                    \n "
"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);       \n"
"		vertexcolor=acolor;         \n"		
"}\n";

const GLchar* fShaderSrc = "#version 330 core              \n"
"out vec4 FragColor;                    \n"
"in vec4 vertexcolor;            \n"
"uniform vec4 ourcolor;            \n"
"void main() {  \n"
	"FragColor = ourcolor*vertexcolor; }  \n";

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
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

	GLuint vShader;
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderSrc, NULL);
	glCompileShader(vShader);

	GLuint fShader;
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderSrc, NULL);
	glCompileShader(fShader);

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);


	//特征值绑定到0号 坐标
	//以后还可以绑定uv等
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0); //位置
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3*sizeof(float))); //颜色
	glEnableVertexAttribArray(1);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timevalue = glfwGetTime();
		float greenvalue = (sin(timevalue) / 2.0f) + 0.5f;
		GLuint vertexcolorcation = glGetUniformLocation(shaderProgram, "ourcolor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexcolorcation, greenvalue, greenvalue, greenvalue, 1.0f);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}