#pragma once
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

#include "DrawableObject.h"
#include "Camera.h"
#include "Controller.h"
#include "Skybox.h"

class Scene
{
public:
	Scene(Controller* controller, Camera* camera, std::vector<Light*> lights, Skybox* skybox = nullptr);
	~Scene();
	void addDrawableObjects(std::vector<DrawableObject*> dObjects);
	void drawObjects();
	
private:
	std::vector<DrawableObject*> dObjects;
	Camera* camera;
	std::vector<Light*> lights;
	Controller* controller;
	Skybox* skybox;
	double mouseX = 0;
	double mouseY = 0;
	double scrollY = 0;
	glm::vec3 movementVector = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec2 windowSize = glm::vec2(1600, 900);
	int selectedObjectId = 0;
	int selectedObjectIndex = -1;
};

