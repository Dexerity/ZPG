#pragma once

#include "Rotate.h"

#include <GLFW/glfw3.h>


class DynamicRotate : public Rotate
{
public:
	DynamicRotate(glm::vec3 m, float speed);
	glm::mat4 applyTransform(glm::mat4 matrix);
private:
	glm::vec3 vector;
	float speed;
	float time = 0;
};

