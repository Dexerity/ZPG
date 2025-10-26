#pragma once

#include <cstddef>
#include <iostream>

#include "Shader.h"
#include "Observer.h"


#include <glm/ext/matrix_float4x4.hpp>


class ShaderProgram
{
public:
	ShaderProgram(Shader& shader);
	~ShaderProgram();
	void applyShaderProgram();
	void setUniform(const std::string& name, const glm::mat4& matrix);
	void setUniform(const std::string& name, const glm::vec3& matrix);
	void setUniform(const std::string& name, const int value);
	void setUniform(const std::string& name, const float value);


private:
	GLuint shaderProgram;
	GLuint idUniform;
	Shader* shader;
};

