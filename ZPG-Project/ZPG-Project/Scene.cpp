#include "Scene.h"

Scene::Scene(Controller* controller, Camera* camera)
{
	this->camera = camera;
	this->controller = controller;
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
	delete controller;
}

void Scene::drawObjects()
{
	camera->updateCamera(this->controller->getMouseX(), this->controller->getMouseY());
	camera->setPosition(this->controller->getMovementVector());

	for (DrawableObject* object : dObjects)
	{
		object->DrawObject();
	}

}
