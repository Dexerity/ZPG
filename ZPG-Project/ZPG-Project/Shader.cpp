#include "Shader.h"

Shader::Shader() 
{

}

void Shader::createShader(GLenum shaderType, const char* shaderString)
{
	if (shaderType == GL_VERTEX_SHADER)
	{
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(this->vertexShader, 1, &shaderString, NULL);
		glCompileShader(this->vertexShader);

		GLint success;
		glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(this->vertexShader, 512, NULL, infoLog);
			fprintf(stderr, "Shader compilation failed: %s\n", infoLog);
			exit(EXIT_FAILURE);
		}
		else
			fprintf(stdout, "vertex shader done\n");
	}
	else if (shaderType == GL_FRAGMENT_SHADER)
	{
		this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->fragmentShader, 1, &shaderString, NULL);
		glCompileShader(this->fragmentShader);

		GLint success;
		glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(this->fragmentShader, 512, NULL, infoLog);
			fprintf(stderr, "Shader compilation failed: %s\n", infoLog);
			exit(EXIT_FAILURE);
		}
		else
			fprintf(stdout, "fragment shader done\n");
	}
}

void Shader::createShaderFromFile(GLenum shaderType, const char* shaderFile)
{
	std::ifstream file(shaderFile);
	if (!file.is_open())
	{
		std::cout << "Unable to open file " << shaderFile << std::endl;
		exit(-1);
	}
	std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	createShader(shaderType, shaderCode.c_str());
}

void Shader::attachShader(GLuint shaderProgram)
{
	glAttachShader(shaderProgram, this->vertexShader);
	glAttachShader(shaderProgram, this->fragmentShader);
}