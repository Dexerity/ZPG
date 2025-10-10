#pragma once

#include <vector>

#include "ATransform.h"
#include "ShaderProgram.h"

class Transformation
{
public:
	Transformation();
	void applyTransforms(ShaderProgram* shaderProgram);
	void resetMatrix();
	std::vector<ATransform*> transforms;
private:
	glm::mat4 matrix;
};

