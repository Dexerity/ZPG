#pragma once

#include "ATransform.h"

class Rotate : public ATransform
{
public:
	Rotate(glm::vec3 m, float angle);
	glm::mat4 applyTransform(glm::mat4 matrix);
private:
	glm::vec3 vector;
	float angle;
};

