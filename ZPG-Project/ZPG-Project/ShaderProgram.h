#pragma once

#include <cstddef>
#include <iostream>
#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram(Shader& shader);
	void setTimeUniform(float time);
	void applyShaderProgram();

private:
	GLuint shaderProgram;
	Shader* shader;
};

