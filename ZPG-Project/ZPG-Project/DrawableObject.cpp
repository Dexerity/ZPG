#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram)
{
	this->model = model;
	this->shaderProgram = shaderProgram;
	this->transformation = new Transformation();
}

void DrawableObject::addTransform(Transformation* transform)
{
	this->transformation = transform;
}

void DrawableObject::DrawObject()
{
	shaderProgram->applyShaderProgram();
	if (this->transformation)
	{
		transformation->applyTransforms(shaderProgram);
	}
	model->drawModel();
	transformation->resetMatrix();
}

DrawableObject::~DrawableObject()
{
	delete this->model;
	delete this->shaderProgram;
	delete this->transformation;
}
