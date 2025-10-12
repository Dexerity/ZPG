#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram)
{
	this->model = model;
	this->shaderProgram = shaderProgram;
	this->transformation = new Transformation();
}

DrawableObject::~DrawableObject()
{
	if (transformation)
	{
		delete transformation;
	}
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

void DrawableObject::addCameraObserver(Camera* camera)
{
	camera->addObserver(this->shaderProgram);
}
