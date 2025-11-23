#pragma once



#include "Translate.h"

#include <vector>

class SetTraslate : public Translate
{
public:
	SetTraslate(std::vector<glm::vec3> points, float speed);
	glm::mat4 applyTransform(glm::mat4 matrix);
private:
	std::vector<glm::vec3> points;
	int currentPointIndex = 0;
	float pointProgress = 0.0f;
	float speed = 0.01f;
};

