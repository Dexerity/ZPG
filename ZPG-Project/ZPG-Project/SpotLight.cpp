#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 color, float intensity, glm::vec3 direction, float alpha) : Light(position, color, intensity)
{
	this->direction = direction;
	this->alpha = alpha;
}

glm::vec3 SpotLight::getDirection()
{
	return this->direction;
}

float SpotLight::getAlpha()
{
	return this->alpha;
}

int SpotLight::getType()
{
	return this->lightType;
}