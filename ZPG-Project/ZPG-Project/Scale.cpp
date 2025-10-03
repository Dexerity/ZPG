#include "Scale.h"

Scale::Scale(glm::vec3 m)
{
	this->vector = m;
}

glm::mat4 Scale::applyTransform(ShaderProgram* shaderProgram, glm::mat4 matrix)
{
	return glm::scale(matrix, this->vector);
}