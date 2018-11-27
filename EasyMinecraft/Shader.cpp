#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	using namespace std;
	cout << "¿ªÊ¼¶ÁÈ¡Shader: " << "vertexPath: " << vertexPath << " fragmentPath: " << fragmentPath << endl;

	ifstream vertexFile;
	ifstream fragmentFile;
	stringstream vertexSStream;
	stringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);


	GLuint vertex;
	try
	{
		if (!vertexFile.is_open())
		{
			throw exception("open vertexfile error");
		}
		vertexSStream << vertexFile.rdbuf();
		vertexString = vertexSStream.str();
		vertexScource = vertexString.c_str();

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexScource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}

	GLuint fragment;
	try
	{
		if (!fragmentFile.is_open())
		{
			throw exception("open fragmentFilefile error");
		}
		fragmentSStream << fragmentFile.rdbuf();
		fragmentString = fragmentSStream.str();
		fragmentScource = fragmentString.c_str();

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentScource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRANGMENT");
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{

}

void Shader::use()
{
	glUseProgram(ID);
}

GLuint Shader::getID()
{
	return ID;
}

void Shader::checkCompileErrors(GLuint ID, std::string type)
{
	using namespace std;

	int success;
	char infoLog[512];

	if (type != "PROGRAM")
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			cout << type << " shader compile error: " << endl
				<< infoLog << endl;
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << "program linking error: " << endl
				<< infoLog << endl;
		}
	}
}