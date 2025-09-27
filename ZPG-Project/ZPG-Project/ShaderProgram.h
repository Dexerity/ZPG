#pragma once

#include <cstddef>
#include <iostream>
#include "Shader.h"
#include "Model.h"

class ShaderProgram
{
public:
	ShaderProgram(Shader& shader);
	void attachShader();
	void setModel(Model& model);
	void applyShaderProgram();

private:
	GLuint shaderProgram;
	Shader* shader;
	Model* model;
};

