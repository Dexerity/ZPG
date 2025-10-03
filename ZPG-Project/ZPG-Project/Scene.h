#pragma once
#include <vector>

#include "DrawableObject.h"

class Scene
{
public:
	Scene();
	void drawObjects();
	std::vector<DrawableObject*> dObjects;
private:
	
};

