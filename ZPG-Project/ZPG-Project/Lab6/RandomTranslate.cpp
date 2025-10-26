#include "RandomTranslate.h"

RandomTranslate::RandomTranslate(glm::vec3 m, int interval) : Translate(m)
{
	this->vector = m;
	this->interval = interval;
}

glm::mat4 RandomTranslate::applyTransform(glm::mat4 matrix)
{
	frames++;
	if (frames >= interval)
	{
		this->direction = getDirection();
		frames = 0;
	}

	return glm::translate(matrix, this->direction);

}

glm::vec3 RandomTranslate::getDirection()
{
	float randX = (((float)(rand() % 10 + 1) / 1000.0) - 0.005f) * this->vector.x;
	float randY = (((float)(rand() % 10 + 1) / 1000.0) - 0.005f) * this->vector.y;
	float randZ = (((float)(rand() % 10 + 1) / 1000.0) - 0.005f) * this->vector.z;

	return glm::vec3(randX, randY, randZ);
}