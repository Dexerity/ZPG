#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(Shader& shader) 
{
	this->shader = &shader;
};

void ShaderProgram::setModel(Model& model) 
{
	this->model = &model;
}

void ShaderProgram::attachShader() 
{
	this->shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, shader->getVertexShader());
	glAttachShader(shaderProgram, shader->getFragmentShader());
	glLinkProgram(shaderProgram);
	
}

void ShaderProgram::applyShaderProgram() 
{ 
	glUseProgram(this->shaderProgram);
	glBindVertexArray(this->model->getVAO());
}
