#include "BezierCurveTransform.h"

BezierCurveTransform::BezierCurveTransform(glm::vec3 P1, glm::vec3 P2, glm::vec3 C1, glm::vec3 C2, float speed)
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

	glm::vec3 tangent = 3.0f * (1 - t) * (1 - t) * (control1 - point1) + 6.0f * (1 - t) * t * (control2 - control1) + 3.0f * t * t * (point2 - control2);
	tangent = glm::normalize(tangent);

	glm::vec3 forward = tangent;
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 right = glm::normalize(glm::cross(up, forward));
	up = glm::normalize(glm::cross(forward, right));

	glm::mat4 rotation = glm::mat4(
		glm::vec4(right, 0),
		glm::vec4(up, 0),
		glm::vec4(forward, 0),
		glm::vec4(0, 0, 0, 1)
	);

	matrix = glm::translate(matrix, curvePoint);

	matrix *= rotation;

	t += speed;
	if (t >= 1.0f || t <= 0.0f)
		speed *= -1;

	return matrix;
}