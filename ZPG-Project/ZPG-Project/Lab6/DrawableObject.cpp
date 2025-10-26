#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram, glm::vec3 color)
{
	this->model = model;
	this->shaderProgram = shaderProgram;
	this->transformation = new Transformation();
	this->color = color;

	shaderProgram->applyShaderProgram();
	shaderProgram->setUniform("objectColor", this->color);
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
		transformation->applyTransforms();
		transformation->setTransforms(shaderProgram);
	}
	

	model->drawModel();
	transformation->resetMatrix();
}

void DrawableObject::Notify(enum SubjectType type)
{
	shaderProgram->applyShaderProgram();

	if(type == SubjectType::CAMERA)
	{
		shaderProgram->setUniform("viewMatrix", camera->getCamera());
		shaderProgram->setUniform("projectionMatrix", camera->getProjectionMatrix());
		shaderProgram->setUniform("cameraPosition", camera->getCameraPosition());
	}
	else if(type == SubjectType::LIGHT)
	{
		for (int i = 0; i < lights.size(); i++)
		{
			std::string lightPos = "lights[" + std::to_string(i) + "].position";
			std::string lightColor = "lights[" + std::to_string(i) + "].color";
			std::string lightIntensity = "lights[" + std::to_string(i) + "].intensity";
			shaderProgram->setUniform(lightPos, lights[i]->getPosition());
			shaderProgram->setUniform(lightColor, lights[i]->getColor());
			shaderProgram->setUniform(lightIntensity, lights[i]->getIntensity());
		}
	}
	
}


DrawableObject::~DrawableObject()
{
	delete this->model;
	delete this->shaderProgram;
	delete this->transformation;
	delete this->camera;

	for (Light* light : lights)
	{
		delete light;
	}
}

void DrawableObject::addSubjects(Camera* camera, std::vector<Light*> lights)
{
	this->camera = camera;
	this->lights = lights;

	this->camera->attachObserver(this);

	for(Light* light : lights)
	{
		light->attachObserver(this);
	}

	shaderProgram->applyShaderProgram();
	shaderProgram->setUniform("lightsCount", (int)lights.size());

	this->Notify(SubjectType::CAMERA);
	this->Notify(SubjectType::LIGHT);
}
