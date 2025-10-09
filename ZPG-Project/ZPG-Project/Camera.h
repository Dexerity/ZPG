#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>


class Camera
{
public:
	Camera();
	glm::mat4 getCamera(void);
	glm::mat4 projectionMatrix;
private:
	glm::vec3 cameraPosition;
	glm::vec3 cameraAngle;
	float alpha = 0;
	float fi = 0;
};

