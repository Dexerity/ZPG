#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Subject.h"

class ALight : public Subject
{
public:
	ALight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity, float alpha, int lightType);
	glm::vec3 getPosition() { return this->position; }
	glm::vec3 getColor() { return this->color; }
	float getIntensity() { return this->intensity; }
	int getType() { return this->lightType; }
	glm::vec3 getDirection() { return this->direction; }
	float getAlpha() { return this->alpha; }

	void updateLight() { return; }
	void setTransformation(Transformation* transform) {}

	float k_c = 1.0f;
	float k_l = 3.0f;
	float k_q = 0.3f;
protected:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 direction;
	float intensity;
	Transformation* transformation = nullptr;
	int lightType;
	float alpha = 0;
};

