#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color, float intensity)
{
	this->position = position;
	this->color = color;
	this->intensity = intensity;
}

Light::~Light()
{
	delete transformation;
}

void Light::updateLight()
{
	if(transformation)
	{
		transformation->resetMatrix();
		transformation->applyTransforms();
		glm::mat4 matrix = transformation->getMatrix();

		this->position += glm::vec3(matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}
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