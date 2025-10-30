#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float intensity) : Light(position, color, intensity)
{
	this->position = position;
	this->color = color;
	this->intensity = intensity;
}

PointLight::~PointLight()
{
	delete transformation;
}

void PointLight::updateLight()
{
	if (transformation)
	{
		transformation->resetMatrix();
		transformation->applyTransforms();
		glm::mat4 matrix = transformation->getMatrix();

		this->position += glm::vec3(matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}
}

glm::vec3 PointLight::getPosition()
{
	return this->position;
}

glm::vec3 PointLight::getColor()
{
	return this->color;
}

float PointLight::getIntensity()
{
	return this->intensity;
}