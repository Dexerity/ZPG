#include "Translate.h"

Translate::Translate(glm::vec3 m)
{
	this->vector = m;
}

glm::mat4 Translate::applyTransform(ShaderProgram* shaderProgram, glm::mat4 matrix)
{
	return glm::translate(matrix, this->vector);
}