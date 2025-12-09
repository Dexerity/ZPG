#include "Flashlight.h"

Flashlight::Flashlight(glm::vec3 color, float intensity) : SpotLight(glm::vec3(0.0f, 0.0f, 0.0f), color, intensity, glm::vec3(0.0f, -1.0f, 0.0f), 0.9)
{
	this->color = color;
	this->intensity = intensity;
	this->alpha = 0.9;
}

void Flashlight::updateDirection(glm::vec3 direction)
{
	this->direction = direction;
}

void Flashlight::updatePosition(glm::vec3 position)
{
	this->position = position;
}

float Flashlight::getAlpha()
{
	return this->alpha;
}

int Flashlight::getType()
{
	return this->lightType;
}