#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram)
{
	this->model = model;
	this->shaderProgram = shaderProgram;
}

void DrawableObject::DrawObject()
{
	shaderProgram->applyShaderProgram();
	model->drawModel();
}
