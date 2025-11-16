#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Subject.h"

class ALight : public Subject
{
public:
	
protected:
	glm::vec3 color;
	float intensity;
	Transformation* transformations;
	ShaderProgram* shaderProgram;
};

