#pragma once

#include "Model.h"
#include "ShaderProgram.h"

class DrawableObject
{
public:
	DrawableObject(Model* model, ShaderProgram* shaderProgram);
	void DrawObject();
private:
	Model* model = nullptr;
	ShaderProgram* shaderProgram = nullptr;

};

