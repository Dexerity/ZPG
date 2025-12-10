#include "ALight.h"

ALight::ALight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity, float alpha, int lightType)
{
	this->position = position;
	this->direction = direction;
	this->color = color;
	this->intensity = intensity;
	this->alpha = alpha;
	this->lightType = lightType;
}
