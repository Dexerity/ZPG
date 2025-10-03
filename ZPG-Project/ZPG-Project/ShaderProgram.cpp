#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader& shader) 
{
	this->shader = &shader;
	this->shaderProgram = glCreateProgram();
	shader.attachShader(this->shaderProgram);
	glLinkProgram(shaderProgram);

	
};

void ShaderProgram::applyShaderProgram() 
{ 
	glUseProgram(this->shaderProgram);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix)
{
	this->idModelTransform = glGetUniformLocation(this->shaderProgram, name.c_str());

	if (this->idModelTransform == -1)
	{
		fprintf(stderr, "Couldn't find uniform %s\n", name);
		exit(EXIT_FAILURE);
	}

	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &matrix[0][0]);
}

