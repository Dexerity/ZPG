#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color, float intensity)
{
	this->position = position;
	this->color = color;
	this->intensity = intensity;
}

glm::vec3 Light::getPosition()
{
	return this->position;
}

glm::vec3 Light::getColor()
{
	return this->color;
}

float Light::getIntensity()
{
	return this->intensity;
}