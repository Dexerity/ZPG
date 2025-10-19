#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader& shader) 
{
	this->shader = &shader;
	this->shaderProgram = glCreateProgram();
	shader.attachShader(this->shaderProgram);
	glLinkProgram(shaderProgram);
};

ShaderProgram::~ShaderProgram() 
{
	glDeleteProgram(this->shaderProgram);
}

void ShaderProgram::applyShaderProgram() 
{ 
	glUseProgram(this->shaderProgram);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix)
{
	this->idUniform = glGetUniformLocation(this->shaderProgram, name.c_str());

	if (this->idUniform == -1)
	{
		fprintf(stderr, "Couldn't find uniform %s\n", name.c_str());
		exit(EXIT_FAILURE);
	}

	glUniformMatrix4fv(idUniform, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::setUniform(const std::string& name, const int value)
{
	this->idUniform = glGetUniformLocation(this->shaderProgram, name.c_str());

	if (this->idUniform == -1)
	{
		fprintf(stderr, "Couldn't find uniform %s\n", name.c_str());
		exit(EXIT_FAILURE);
	}

	glUniform1i(idUniform, value);
}

void ShaderProgram::setUniform(const std::string& name, const float value)
{
	this->idUniform = glGetUniformLocation(this->shaderProgram, name.c_str());
	if (this->idUniform == -1) {
		fprintf(stderr, "Couldn't find uniform %s\n", name.c_str());
		exit(EXIT_FAILURE);
	}
	glUniform1f(idUniform, value);
}



void ShaderProgram::Notify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	this->setUniform("viewMatrix", viewMatrix);
	this->setUniform("projectionMatrix", projectionMatrix);
}

