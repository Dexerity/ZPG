#pragma once

#include <glm/ext/matrix_float4x4.hpp>

class Observer
{
public:
	virtual void Notify(enum SubjectType type) = 0;
};