#pragma once

#include "DirectionLight.h"

class Flashlight : public DirectionLight
{
public:
	Flashlight(glm::vec3 color, float intensity);
	void updateDirection(glm::vec3 direction);
	void updatePosition(glm::vec3 position);
	glm::vec3 getColor() { return color; }
	glm::vec3 getDirection() { return direction; }
	glm::vec3 getPosition() { return position; }
	float getIntensity() { return intensity; }

private:
	glm::vec3 color;
	float intensity;
	glm::vec3 direction;
	int lightType = 1;
};

