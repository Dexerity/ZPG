#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(Shader& shader) 
{
	this->shader = &shader;
	this->shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, this->shader->getVertexShader());
	glAttachShader(shaderProgram, this->shader->getFragmentShader());
	glLinkProgram(shaderProgram);
};

void ShaderProgram::applyShaderProgram() 
{ 
	glUseProgram(this->shaderProgram);
}

void ShaderProgram::setTimeUniform(float time) 
{
	GLint timeLocation = glGetUniformLocation(this->shaderProgram, "time");
	if (timeLocation != -1) {
		glUseProgram(this->shaderProgram);
		glUniform1f(timeLocation, time);
	}
}
