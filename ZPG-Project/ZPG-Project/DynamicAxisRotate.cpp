#include "DynamicAxisRotate.h"

DynamicAxisRotate::DynamicAxisRotate(glm::vec3 rotation, glm::vec3 point, float speed) : DynamicRotate(rotation, speed)
{
	this->rotation = rotation;
}