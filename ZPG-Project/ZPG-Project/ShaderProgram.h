#pragma once

#include <cstddef>
#include <iostream>
#include "Shader.h"

#include <glm/ext/matrix_float4x4.hpp>


class ShaderProgram
{
public:
	ShaderProgram(Shader& shader);
	void applyShaderProgram();
	void setUniform(const std::string& name, const glm::mat4& matrix);

private:
	GLuint shaderProgram;
	GLuint idModelTransform;
	Shader* shader;
};

