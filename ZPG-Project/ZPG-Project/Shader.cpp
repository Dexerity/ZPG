#include "Shader.h"

Shader::Shader(const char* vertexString,const char* fragmentString) 
{
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShader, 1, &vertexString, NULL);
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

	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragmentShader, 1, &fragmentString, NULL);
	glCompileShader(this->fragmentShader);

	glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(this->fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "Shader compilation failed: %s\n", infoLog);
		exit(EXIT_FAILURE);
	}
}

GLuint Shader::getVertexShader()
{ 
	return this->vertexShader; 
}

GLuint Shader::getFragmentShader()
{ 
	return this->fragmentShader; 
}