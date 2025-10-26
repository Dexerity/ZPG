#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader& shader) 
{
	this->shader = &shader;
	this->shaderProgram = glCreateProgram();
	shader.attachShader(this->shaderProgram);
	glLinkProgram(shaderProgram);

	this->applyShaderProgram();

	setUniform("k_l", 0.3f);
	setUniform("k_q", 3.f);
	setUniform("k_c", 1.0f);
};

ShaderProgram::~ShaderProgram() 
{
	glDeleteProgram(this->shaderProgram);

	delete this->shader;
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
		//fprintf(stderr, "Couldn't find uniform %s\n", name.c_str());
		//exit(EXIT_FAILURE);
	}

	glUniformMatrix4fv(idUniform, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& vector)
{
	this->idUniform = glGetUniformLocation(this->shaderProgram, name.c_str());

	if (this->idUniform == -1)
	{
		//fprintf(stderr, "Couldn't find uniform %s\n", name.c_str());
		//exit(EXIT_FAILURE);
	}

	glUniform3f(idUniform, vector.x, vector.y, vector.z);

}

void ShaderProgram::setUniform(const std::string& name, const int value)
{
	this->idUniform = glGetUniformLocation(this->shaderProgram, name.c_str());

	if (this->idUniform == -1)
	{
		//fprintf(stderr, "Couldn't find uniform %s\n", name.c_str());
		//exit(EXIT_FAILURE);
	}

	glUniform1i(idUniform, value);
}

void ShaderProgram::setUniform(const std::string& name, const float value)
{
	this->idUniform = glGetUniformLocation(this->shaderProgram, name.c_str());
	if (this->idUniform == -1) {
		//fprintf(stderr, "Couldn't find uniform %s\n", name.c_str());
		//exit(EXIT_FAILURE);
	}
	glUniform1f(idUniform, value);
}

