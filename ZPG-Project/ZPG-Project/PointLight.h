#pragma once

#include <glm/glm.hpp>

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight(glm::vec3 position, glm::vec3 color, float intensity);
	~PointLight();
	glm::vec3 getPosition();
	glm::vec3 getColor();
	float getIntensity();
	void setTransformation(Transformation* transformation) { this->transformation = transformation; }
	void updateLight();
	int lightType = 1;
private:
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	Transformation* transformation = nullptr;
};

