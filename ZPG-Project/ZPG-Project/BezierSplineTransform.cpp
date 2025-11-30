#include "BezierSplineTransform.h"

BezierSplineTransform::BezierSplineTransform(float speed)
{
    this->speed = speed;
    this->currentCurve = 0;
}

void BezierSplineTransform::addPoint(glm::vec3 point)
{
    controlPoints.push_back(point);
}

glm::mat4 BezierSplineTransform::applyTransform(glm::mat4 matrix)
{
    if (controlPoints.size() < 4)
        return matrix;

    int curveCount = (controlPoints.size() - 1) / 3;
    //currentCurve = glm::clamp(currentCurve, 0, curveCount - 1);

    glm::vec3 P0 = controlPoints[currentCurve * 3];
    glm::vec3 P1 = controlPoints[currentCurve * 3 + 1];
    glm::vec3 P2 = controlPoints[currentCurve * 3 + 2];
    glm::vec3 P3 = controlPoints[currentCurve * 3 + 3];

    glm::mat4 A = glm::mat4(
        glm::vec4(-1, 3, -3, 1),
        glm::vec4(3, -6, 3, 0),
        glm::vec4(-3, 3, 0, 0),
        glm::vec4(1, 0, 0, 0)
    );

    glm::mat4x3 B = glm::mat4x3(P0, P1, P2, P3);

    glm::vec4 p = glm::vec4(t * t * t, t * t, t, 1.0f);

    glm::vec3 curvePoint = p * A * glm::transpose(B);

    glm::vec3 tangent = 3.0f * (1 - t) * (1 - t) * (P1 - P0) + 6.0f * (1 - t) * t * (P2 - P1) + 3.0f * t * t * (P3 - P2);
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
    if (t >= 1.0f)
    {
        t = 0.0f;
        currentCurve++;

        if (currentCurve >= curveCount)
            currentCurve = 0;
    }

    return matrix;
}