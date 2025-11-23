#include "SetTraslate.h"

SetTraslate::SetTraslate(std::vector<glm::vec3> points, float speed) : Translate(glm::vec3(0.0f, 0.0f, 0.0f))
{
	this->points = points;
	this->speed = speed;
}

glm::mat4 SetTraslate::applyTransform(glm::mat4 matrix)
{
	if (points.size() == 0)
		return matrix;

	if(this->pointProgress >= 1.0f)
	{
		this->currentPointIndex++;
		if(this->currentPointIndex >= points.size())
		{
			this->currentPointIndex = 0;
		}
		this->pointProgress = 0.0f;
	}

	glm::vec3 currentPoint = points[this->currentPointIndex];
	glm::vec3 nextPoint = points[(this->currentPointIndex + 1) % points.size()];
	glm::vec3 direction = nextPoint - currentPoint;

	this->pointProgress += this->speed;

	return glm::translate(matrix, currentPoint + direction * this->pointProgress);
}