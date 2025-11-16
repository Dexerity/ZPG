#include "DirectionLight.h"

DirectionLight::DirectionLight(glm::vec3 position, glm::vec3 color, float intensity, glm::vec3 direction) : Light(position, color, intensity)
{
	this->direction = direction;
}

glm::vec3 DirectionLight::getDirection()
{
	return this->direction;
}

int DirectionLight::getType()
{
	return this->lightType;
}
