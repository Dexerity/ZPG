#pragma once

#include "ALight.h"

class DirectionLight : public ALight
{
public:
	DirectionLight(glm::vec3 color, float intensity, glm::vec3 direction);
	glm::vec3 getDirection();
	int getType();

private:
	int lightType = 1;
	glm::vec3 direction;
};

