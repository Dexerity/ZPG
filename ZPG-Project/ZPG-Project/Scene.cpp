#include "Scene.h"

Scene::Scene()
{

}

void Scene::drawObjects()
{
	for (DrawableObject* object : dObjects)
	{
		object->DrawObject();
	}
}
