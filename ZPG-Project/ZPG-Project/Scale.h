#pragma once

#include "ATransform.h"

class Scale : public ATransform
{
public:
	Scale(glm::vec3 m);
	glm::mat4 applyTransform(glm::mat4 matrix);
private:
	glm::vec3 vector;
};

