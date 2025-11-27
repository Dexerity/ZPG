#pragma once

#include "ATransform.h"

class CustomTransform : public ATransform
{
public:
	CustomTransform(glm::mat4 m) { this->matrix = m; }
	glm::mat4 applyTransform(glm::mat4 matrix) override { return matrix * this->matrix; }
private:
	glm::mat4 matrix;
};
