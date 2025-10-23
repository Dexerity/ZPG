#pragma once

#include <cstddef>
#include <iostream>

#include "Shader.h"
#include "Observer.h"
#include "Camera.h"
#include "Light.h"

#include <glm/ext/matrix_float4x4.hpp>


class ShaderProgram : public Observer
{
public:
	ShaderProgram(Shader& shader);
	~ShaderProgram();
	void applyShaderProgram();
	void attachCamera(Camera* camera);
	void attachLight(Light* light);
	void setUniform(const std::string& name, const glm::mat4& matrix);
	void setUniform(const std::string& name, const glm::vec3& matrix);
	void setUniform(const std::string& name, const int value);
	void setUniform(const std::string& name, const float value);
	void Notify() override;

private:
	GLuint shaderProgram;
	GLuint idUniform;
	Shader* shader;
	Camera* camera;
	Light* light;
};

