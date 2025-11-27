#pragma once

#include "DynamicRotate.h"

class DynamicAxisRotate : public DynamicRotate
{
public:
	DynamicAxisRotate(glm::vec3 v, glm::vec3 point, float speed);
	glm::mat4 applyTransform(glm::mat4 matrix);
private:
	glm::vec3 rotation;
	glm::vec3 point;
};

