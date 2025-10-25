#include "Scene.h"
#include <unordered_map>
#include <string>

Scene::Scene(Controller* controller, Camera* camera, std::vector<Light*> lights)
{
	this->camera = camera;
	this->controller = controller;
	this->lights = lights;
}

Scene::~Scene()
{
	for (DrawableObject* object : dObjects)
	{
		if (object)
		{
			delete object;
		}
	}

	for (Light* light : lights)
	{
		if (light)
		{
			delete light;
		}
	}

	delete controller;
	delete camera;
}

void Scene::addDrawableObjects(std::vector<DrawableObject*> dObjects)
{
	this->dObjects = dObjects;
	for (DrawableObject* object : dObjects)
	{
		object->addSubjects(this->camera, this->lights);
	}
}

void Scene::drawObjects()
{
	if (this->controller->getMouseX() != this->mouseX || this->controller->getMouseY() != this->mouseY || this->controller->getMovementVector() != glm::vec3(0.0f))
	{
		this->mouseX = this->controller->getMouseX();
		this->mouseY = this->controller->getMouseY();
		camera->updateCamera(this->mouseX, this->mouseY);
		camera->setPosition(this->controller->getMovementVector());
	}

	if (this->controller->getWindowSize() != this->windowSize)
	{
		this->windowSize = this->controller->getWindowSize();
		camera->updateProjectionMatrix(this->windowSize.x, this->windowSize.y, this->scrollY);
	}

	if (this->controller->getScrollY() != 0)
	{
		this->scrollY = this->controller->getScrollY();
		camera->updateProjectionMatrix(this->windowSize.x, this->windowSize.y, this->scrollY);
		this->controller->resetScrollY();
		this->scrollY = 0;
	}

	for (Light* light : lights)
	{
		light->updateLight();
	}

	for (DrawableObject* object : dObjects)
	{
		object->Notify(SubjectType::LIGHT);
	}

	for (DrawableObject* object : dObjects)
	{
		object->DrawObject();
	}

}
