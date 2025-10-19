#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Camera.h"

class DrawableObject
{
public:
	DrawableObject(Model* model, ShaderProgram* shaderProgram);
	~DrawableObject();
	void addTransform(Transformation* transform);
	void DrawObject();
	void addCameraObserver(Camera* camera);
	
private:
	Model* model = nullptr;
	ShaderProgram* shaderProgram = nullptr;
	Transformation* transformation;
};

