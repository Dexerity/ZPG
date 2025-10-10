#include "Scene.h"

Scene::Scene(Controller* controller)
{
	this->camera = Camera();
	this->controller = controller;
}

void Scene::drawObjects()
{
	camera.updateCamera(this->controller->getMouseX(), this->controller->getMouseY());
	camera.setPosition(this->controller->getMovementVector());

	for (DrawableObject* object : dObjects)
	{
		object->DrawObject(this->camera);
	}

}
