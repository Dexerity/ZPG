#pragma once
#include <vector>

#include "DrawableObject.h"
#include "Camera.h"
#include "Controller.h"

class Scene
{
public:
	Scene(Controller* controller);
	void drawObjects();
	std::vector<DrawableObject*> dObjects;
private:
	Camera camera;
	Controller* controller;
};

