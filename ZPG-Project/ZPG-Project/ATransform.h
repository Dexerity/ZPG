#pragma once

#include "ShaderProgram.h"

#include <glm/ext/matrix_transform.hpp>


class ATransform
{
public:
	virtual glm::mat4 applyTransform(glm::mat4 matrix) = 0;
};

