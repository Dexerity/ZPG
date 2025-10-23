#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader& shader) 
{
	this->shader = &shader;
	this->shaderProgram = glCreateProgram();
	shader.attachShader(this->shaderProgram);
	glLinkProgram(shaderProgram);
	this->camera = nullptr;
	this->light = nullptr;
};

ShaderProgram::~ShaderProgram() 
{
	glDeleteProgram(this->shaderProgram);
}

void ShaderProgram::applyShaderProgram() 
{ 
	glUseProgram(this->shaderProgram);
}

void ShaderProgram::attachCamera(Camera* camera)
{
	this->camera = camera;
	this->camera->attachObserver(this);
}

void ShaderProgram::attachLight(Light* light)
{
	this->light = light;
	this->light->attachObserver(this);
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

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& vector)
{
	this->idUniform = glGetUniformLocation(this->shaderProgram, name.c_str());

	if (this->idUniform == -1)
	{
		fprintf(stderr, "Couldn't find uniform %s\n", name.c_str());
		exit(EXIT_FAILURE);
	}

	glUniform3f(idUniform, vector.x, vector.y, vector.z);

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



void ShaderProgram::Notify()
{
	applyShaderProgram();

	if (camera) {
		setUniform("viewMatrix", camera->getCamera());
		setUniform("projectionMatrix", camera->getProjectionMatrix());
		//setUniform("cameraPosition", camera->getCameraPosition());
	}

	if (light) {
		setUniform("lightPosition", light->getPosition());
		setUniform("lightColor", light->getColor());
		setUniform("lightIntensity", light->getIntensity());
	}

}

