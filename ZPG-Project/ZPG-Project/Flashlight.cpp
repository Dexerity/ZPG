#include "Flashlight.h"

Flashlight::Flashlight(glm::vec3 color, float intensity) : DirectionLight(glm::vec3(0.0f, 0.0f, 0.0f), color, intensity, glm::vec3(0.0f, -1.0f, 0.0f))
{
	this->color = color;
	this->intensity = intensity;
}

void Flashlight::updateDirection(glm::vec3 direction)
{
	this->direction = direction;
}

void Flashlight::updatePosition(glm::vec3 position)
{
	this->position = position;
}