#pragma once

#include <vector>

#include "ATransform.h"
#include "ShaderProgram.h"

class Transformation
{
public:
	Transformation();
	void applyTransforms();
	void setTransforms(ShaderProgram* shaderProgram);
	void resetMatrix();
	glm::mat4 getMatrix() { return matrix; }
	std::vector<ATransform*> transforms;
private:
	glm::mat4 matrix;
};

