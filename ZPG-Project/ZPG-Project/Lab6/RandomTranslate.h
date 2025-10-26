#pragma once

#include "Translate.h"

#include <GLFW/glfw3.h>
#include <random>

class RandomTranslate : public Translate
{
public:
	RandomTranslate(glm::vec3 m, int interval);
	glm::mat4 applyTransform(glm::mat4 matrix);
	glm::vec3 getDirection();
private:
	glm::vec3 vector;
	glm::vec3 direction;
	int frames = 9999;
	int interval;
};

