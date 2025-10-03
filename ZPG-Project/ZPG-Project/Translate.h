#pragma once

#include "ATransform.h"

class Translate : public ATransform
{
public:
	Translate(glm::vec3 m);
	glm::mat4 applyTransform(ShaderProgram* shaderProgram, glm::mat4 matrix);
private:
	glm::vec3 vector;
};

