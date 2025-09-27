#include "Shader.h"

Shader::Shader(const char* vertexString,const char* fragmentString) 
{
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShader, 1, &vertexString, NULL);
	glCompileShader(this->vertexShader);


	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragmentShader, 1, &fragmentString, NULL);
	glCompileShader(this->fragmentShader);
}

GLuint Shader::getVertexShader()
{ 
	return this->vertexShader; 
}

GLuint Shader::getFragmentShader()
{ 
	return this->fragmentShader; 
}