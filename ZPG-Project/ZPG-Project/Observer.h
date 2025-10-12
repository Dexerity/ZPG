#pragma once

#include <glm/ext/matrix_float4x4.hpp>

class Observer
{
public:
	virtual void Notify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) = 0;
};