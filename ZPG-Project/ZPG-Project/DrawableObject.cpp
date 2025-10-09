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

void DrawableObject::addCameraMatrises(Camera camera)
{
	this->shaderProgram->setUniform("viewMatrix", camera.getCamera());
	this->shaderProgram->setUniform("projectionMatrix", camera.projectionMatrix);
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
