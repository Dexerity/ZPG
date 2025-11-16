#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram, glm::vec3 color, Texture* texture)
{
	this->model = model;
	this->shaderProgram = shaderProgram;
	this->transformation = new Transformation();
	this->color = color;
	this->origColor = color;
	this->texture = texture;

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
	if (this->texture)
	{
		texture->bind(0);
	}

	glStencilFunc(GL_ALWAYS, this->ID, 0xFF);

	shaderProgram->setUniform("objectColor", color);
	shaderProgram->setUniform("textureUnitID", 0);
	

	model->drawModel();
	texture->unbind();
	transformation->resetMatrix();
	glUseProgram(0);
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
			std::string lightType = "lights[" + std::to_string(i) + "].type";
			std::string lightPos = "lights[" + std::to_string(i) + "].position";
			std::string lightColor = "lights[" + std::to_string(i) + "].color";
			std::string lightIntensity = "lights[" + std::to_string(i) + "].intensity";
			std::string l_k_l = "lights[" + std::to_string(i) + "].k_l";
			std::string l_k_q = "lights[" + std::to_string(i) + "].k_q";
			std::string l_k_c = "lights[" + std::to_string(i) + "].k_c";
			std::string lightRange = "lights[" + std::to_string(i) + "].range";
			shaderProgram->setUniform(lightType, lights[i]->getType());
			shaderProgram->setUniform(lightPos, lights[i]->getPosition());
			shaderProgram->setUniform(lightColor, lights[i]->getColor());
			shaderProgram->setUniform(lightIntensity, lights[i]->getIntensity());
			shaderProgram->setUniform(l_k_l, 3.0f);
			shaderProgram->setUniform(l_k_q, 0.3f);
			shaderProgram->setUniform(l_k_c, 1.0f);
			shaderProgram->setUniform(lightRange, 5.0f);

			if (lights[i]->getType() == 1)
			{
				std::string lightDirection = "lights[" + std::to_string(i) + "].direction";
				shaderProgram->setUniform(lightDirection, lights[i]->getDirection());
			}
			if (lights[i]->getType() == 2)
			{
				std::string lightDirection = "lights[" + std::to_string(i) + "].direction";
				std::string lightAlpha = "lights[" + std::to_string(i) + "].alpha";
				shaderProgram->setUniform(lightDirection, lights[i]->getDirection());
				shaderProgram->setUniform(lightAlpha, lights[i]->getAlpha());
			}
		}
	}
	
}


DrawableObject::~DrawableObject()
{
	/*delete this->model;
	delete this->shaderProgram;*/
	delete this->transformation;

	if(this->camera)
		this->camera->detachObserver(this);

	for (Light* light : lights)
	{
		if(light)
			light->detachObserver(this);
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

void DrawableObject::setID(int ID)
{
	this->ID = ID;
}

int DrawableObject::getID()
{
	return this->ID;
}

void DrawableObject::setColor(glm::vec3 color)
{
	this->color = color;
}

void DrawableObject::resetOrigColor()
{
	this->color = this->origColor;
}