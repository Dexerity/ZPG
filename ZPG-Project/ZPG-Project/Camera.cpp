#include "Camera.h"


Camera::Camera()
{
	this->projectionMatrix = glm::perspective(90.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	this->cameraPosition = glm::vec3(1.0f, 0.0f, 1.0f);
}

glm::mat4 Camera::getCamera(void) 
{
	this->cameraAngle.x = sin(alpha) * cos(fi);
	this->cameraAngle.z = sin(alpha) * sin(fi);
	this->cameraAngle.y = cos(alpha);

	return glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraAngle, glm::vec3(0.0f, 1.0f, 0.0f));
}
