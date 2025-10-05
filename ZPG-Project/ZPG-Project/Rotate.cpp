#include "Rotate.h"

Rotate::Rotate(glm::vec3 m, float angle)
{
	this->vector = m;
	this->angle = angle;
}

glm::mat4 Rotate::applyTransform(glm::mat4 matrix)
{
	return glm::rotate(matrix, glm::radians(this->angle), this->vector);
}