#pragma once

#include "Light.h"

class DirectionLight : public Light
{
public:
	DirectionLight(glm::vec3 position, glm::vec3 color, float intensity, glm::vec3 direction);
	glm::vec3 getDirection();
	int getType();
private:
	int lightType = 1;
	glm::vec3 direction;
};

