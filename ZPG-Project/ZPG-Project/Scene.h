#pragma once
#include <vector>

#include "DrawableObject.h"
#include "Camera.h"

class Scene
{
public:
	Scene();
	void drawObjects();
	std::vector<DrawableObject*> dObjects;
private:
	Camera* camera;
};

