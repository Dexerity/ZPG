#pragma once

#include <glm/glm.hpp>

#include "Subject.h"

class Light : public Subject
{
public:
	Light(glm::vec3 position, glm::vec3 color, float intensity);
	glm::vec3 getPosition();
	glm::vec3 getColor();
	float getIntensity();

private:
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
};

