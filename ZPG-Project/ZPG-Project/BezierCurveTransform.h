#pragma once

#include "ATransform.h"

class BezierCurveTransform : public ATransform
{
public:
	BezierCurveTransform(glm::vec3 P1, glm::vec3 P2, glm::vec3 C1, glm::vec3 C2, double speed);
	glm::mat4 applyTransform(glm::mat4 matrix) override;
private:
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 control1;
	glm::vec3 control2;
	double t;
	double speed;
};

