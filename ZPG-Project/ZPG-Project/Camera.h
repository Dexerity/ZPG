#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <vector>

#include "Subject.h"


class Camera : public Subject
{
public:
	Camera();
	glm::mat4 getCamera(void);
	void updateCamera(double x, double y);
	void setPosition(glm::vec3 position);
	glm::vec3 getCameraPosition();
	glm::mat4 getProjectionMatrix();


private:
	glm::mat4 projectionMatrix;
	std::vector<Observer*> observers;
	glm::vec3 cameraPosition;
	glm::vec3 cameraAngle;
	float alpha = 90;
	float fi = 0;
};

