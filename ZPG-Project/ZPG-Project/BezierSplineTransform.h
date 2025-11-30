#pragma once

#include "ATransform.h"

#include <vector>

class BezierSplineTransform : public ATransform
{
public:
    BezierSplineTransform(float speed = 0.01);
    void addPoint(glm::vec3 point);
    glm::mat4 applyTransform(glm::mat4 matrix) override;
private:
    std::vector<glm::vec3> controlPoints;
    float t = 0.0f;
    float speed = 0.01f;                   
    int currentCurve = 0;
};

