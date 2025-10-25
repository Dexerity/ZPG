#pragma once

#include <glm/glm.hpp>

#include "Transformation.h"
#include "RandomTranslate.h"
#include "Subject.h"


class Transformation;

class Light : public Subject
{
public:
	Light(glm::vec3 position, glm::vec3 color, float intensity);
	~Light();
	glm::vec3 getPosition();
	glm::vec3 getColor();
	float getIntensity();
	void setTransformation(Transformation* transformation) { this->transformation = transformation; }
	void updateLight();

private:
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	Transformation* transformation = nullptr;
};

