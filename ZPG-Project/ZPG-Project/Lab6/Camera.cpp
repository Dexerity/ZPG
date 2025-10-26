#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>


Camera::Camera()
{
	this->projectionMatrix = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	this->cameraPosition = glm::vec3(0.0f, 0.2f, 0.9f);
	this->cameraAngle = glm::vec3(0.0f, 0.0f, -1.0f);
}

Camera::~Camera()
{
	for (auto observer : observers)
	{
		delete observer;
	}
}

void Camera::updateCamera(double x, double y)
{
	this->fi = glm::radians(((x / 1600) * 360.0f));
	this->alpha = glm::radians(-((y / 900)) * 180.0f);

	//this->notifyObservers();
}

void Camera::updateProjectionMatrix(int width, int height, double scrollOff)
{
	this->FOV -= scrollOff * 5.0f;
	
	if (this->FOV > 130.f)
		this->FOV = 130.f;
	if (this->FOV < 45.f)
		this->FOV = 45.f;

	this->projectionMatrix = glm::perspective(glm::radians(this->FOV), (float)width / (float)height, 0.1f, 100.0f);
	this->notifyObservers(SubjectType::CAMERA);
}

void Camera::setPosition(glm::vec3 position)
{
	position = position * 0.1f;
	
	cameraPosition.x += position.x * sin(fi) - position.z * cos(fi);
	cameraPosition.z -= position.x * cos(fi) + position.z * sin(fi);
	cameraPosition.y += position.y;
	

	/*if(this->cameraPosition.x > 1.0f)
		this->cameraPosition.x = 1.0f;
	if (this->cameraPosition.x < -1.0f)
		this->cameraPosition.x = -1.0f;

	if (this->cameraPosition.z > 1.0f)
		this->cameraPosition.z = 1.0f;
	if (this->cameraPosition.z < -1.0f)
		this->cameraPosition.z = -1.0f;*/

	this->notifyObservers(SubjectType::CAMERA);
}

glm::vec3 Camera::getCameraPosition()
{
	return this->cameraPosition;
}

glm::mat4 Camera::getCamera(void) 
{
	//fi = fmod(glfwGetTime(), 360.0f);

	this->cameraAngle.x = sin(alpha) * cos(fi);
	this->cameraAngle.z = sin(alpha) * sin(fi);
	this->cameraAngle.y = cos(alpha);

	//return glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	return glm::lookAt(this->cameraPosition, this->cameraAngle + this->cameraPosition, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix()
{
	return this->projectionMatrix;
}
