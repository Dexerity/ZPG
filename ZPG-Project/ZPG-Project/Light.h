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
	int getType();
	glm::vec3 getDirection();
	float getAlpha();

protected:
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	Transformation* transformation = nullptr;
	int lightType = 0;
	float alpha = 0;
};

