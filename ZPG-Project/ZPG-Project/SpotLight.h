#pragma once

#include "Light.h"

class SpotLight : public Light
{
public:
	SpotLight(glm::vec3 position, glm::vec3 color, float intensity, glm::vec3 direction, float alpha);
	glm::vec3 getDirection();
	float getAlpha();
	int getType();
private:
	int lightType = 2;
	glm::vec3 direction;
	float alpha;
};

