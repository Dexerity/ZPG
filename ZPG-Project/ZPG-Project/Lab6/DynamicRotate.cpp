#include "DynamicRotate.h"

DynamicRotate::DynamicRotate(glm::vec3 vector, float speed) : Rotate(vector, 0.0f)
{
	this->vector = vector;
	this->speed = speed;
}

glm::mat4 DynamicRotate::applyTransform(glm::mat4 matrix)
{
	this->time = glfwGetTime();
	float dynamicAngle = this->time * this->speed;
	return glm::rotate(matrix, dynamicAngle, this->vector);
}

