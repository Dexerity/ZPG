#include "Rotate.h"

Rotate::Rotate(glm::vec3 m, float angle)
{
	this->vector = m;
	this->angle = angle;
}

glm::mat4 Rotate::applyTransform(ShaderProgram* shaderProgram, glm::mat4 matrix)
{
	return glm::rotate(matrix, this->angle, this->vector);
}