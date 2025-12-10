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

	glm::vec3 mat;
	float h;

	if(this->material)
	{
		mat = this->material->getMaterial();
		h = this->material->getH();

		shaderProgram->setUniform("ra", mat.x);
		shaderProgram->setUniform("rd", mat.y);
		shaderProgram->setUniform("rs", mat.z);
		shaderProgram->setUniform("h", h);
	}
	else
	{
		shaderProgram->setUniform("ra", 0.1f);
		shaderProgram->setUniform("rd", 1.0f);
		shaderProgram->setUniform("rs", 1.0f);
		shaderProgram->setUniform("h", 32);
	}
	

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

		if (flashlight)
		{
			this->flashlight->updatePosition(camera->getCameraPosition());
			this->flashlight->updateDirection(camera->getCameraDir());
			Notify(SubjectType::LIGHT);
		}
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
			shaderProgram->setUniform(l_k_l, lights[i]->k_l);
			shaderProgram->setUniform(l_k_q, lights[i]->k_q);
			shaderProgram->setUniform(l_k_c, lights[i]->k_c);
			shaderProgram->setUniform(lightRange, 500.0f);

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
		if(flashlight)
		{
			int i = lights.size() - 1;
			std::string lightType = "lights[" + std::to_string(i) + "].type";
			std::string lightPos = "lights[" + std::to_string(i) + "].position";
			std::string lightColor = "lights[" + std::to_string(i) + "].color";
			std::string lightIntensity = "lights[" + std::to_string(i) + "].intensity";
			std::string lightDirection = "lights[" + std::to_string(i) + "].direction";
			std::string lightAlpha = "lights[" + std::to_string(i) + "].alpha";
			std::string l_k_l = "lights[" + std::to_string(i) + "].k_l";
			std::string l_k_q = "lights[" + std::to_string(i) + "].k_q";
			std::string l_k_c = "lights[" + std::to_string(i) + "].k_c";
			shaderProgram->setUniform(lightType, flashlight->getType());
			shaderProgram->setUniform(lightPos, flashlight->getPosition());
			shaderProgram->setUniform(lightIntensity, flashlight->getIntensity());
			if(flashlight->isActive == true)
				shaderProgram->setUniform(lightColor, flashlight->getColor());
			else
				shaderProgram->setUniform(lightColor, glm::vec3(0.0f));
			shaderProgram->setUniform(lightDirection, flashlight->getDirection());
			shaderProgram->setUniform(lightAlpha, flashlight->getAlpha());
			shaderProgram->setUniform(l_k_l, flashlight->k_l);
			shaderProgram->setUniform(l_k_q, flashlight->k_q);
			shaderProgram->setUniform(l_k_c, flashlight->k_c);
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

	for (ALight* light : lights)
	{
		if(light)
			light->detachObserver(this);
	}
}

void DrawableObject::addSubjects(Camera* camera, std::vector<ALight*> lights)
{
	this->camera = camera;
	this->lights = lights;

	this->camera->attachObserver(this);

	for(ALight* light : lights)
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