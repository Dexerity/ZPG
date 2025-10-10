#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Camera.h"

class DrawableObject
{
public:
	DrawableObject(Model* model, ShaderProgram* shaderProgram);
	void addTransform(Transformation* transform);
	void addCameraMatrises(Camera camera);
	void DrawObject(Camera camera);
private:
	Model* model = nullptr;
	ShaderProgram* shaderProgram = nullptr;
	Transformation* transformation;
};

