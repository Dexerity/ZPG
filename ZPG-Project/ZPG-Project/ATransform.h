#pragma once

#include "ShaderProgram.h"

#include <glm/ext/matrix_transform.hpp>


class ATransform
{
public:
	virtual glm::mat4 applyTransform(ShaderProgram* shaderProgram, glm::mat4 matrix) = 0;
};

