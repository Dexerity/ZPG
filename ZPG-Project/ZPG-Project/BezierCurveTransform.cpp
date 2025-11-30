#include "BezierCurveTransform.h"

BezierCurveTransform::BezierCurveTransform(glm::vec3 P1, glm::vec3 P2, glm::vec3 C1, glm::vec3 C2, double speed)
{
	this->point1 = P1;
	this->point2 = P2;
	this->control1 = C1;
	this->control2 = C2;
	this->t = 0;
	this->speed = speed;
}

glm::mat4 BezierCurveTransform::applyTransform(glm::mat4 matrix)
{
	glm::mat4 A = glm::mat4(
		glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0.0),
		glm::vec4(-3.0, 3.0, 0.0, 0.0),
		glm::vec4(1.0, 0.0, 0.0, 0.0)
	);

	glm::mat4x3 B = glm::mat4x3(point1, control1, control2, point2);

	glm::vec4 p = glm::vec4(t * t * t, t * t, t, 1.0f);

	glm::vec3 curvePoint = p * A * glm::transpose(B);

	matrix = glm::translate(matrix, curvePoint);

	t += speed;
	if (t >= 1.0f || t <= 0.0f)
		speed *= -1;

	return matrix;
}