#include "DirectionLight.h"

DirectionLight::DirectionLight(glm::vec3 color, float intensity, glm::vec3 direction) : ALight(glm::vec3(1.0f), direction, color, intensity, 1, 1)
{
	this->direction = direction;
	this->lightType = 1;
}

glm::vec3 DirectionLight::getDirection()
{
	return this->direction;
}

int DirectionLight::getType()
{
	return this->lightType;
}
