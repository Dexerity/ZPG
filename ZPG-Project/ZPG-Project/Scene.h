#pragma once
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

#include "DrawableObject.h"
#include "Camera.h"
#include "Controller.h"
#include "Skybox.h"
#include "Flashlight.h"

#include "Scale.h"

#include "SetTraslate.h"
#include "BezierSplineTransform.h"
#include "Rotate.h"

class Scene
{
public:
	Scene(Controller* controller, Camera* camera, std::vector<Light*> lights, Skybox* skybox = nullptr, int sceneState = 0);
	~Scene();
	void addDrawableObjects(std::vector<DrawableObject*> dObjects);
	void drawObjects();
	void addAObject(ShaderProgram* shaderProgram, Model* model, glm::vec3 color, Texture* texture = nullptr);
	void setFlashlight(Flashlight* flashlight);
private:
	int sceneState = 0;
	int score = 0;
	std::vector<DrawableObject*> dObjects;
	Camera* camera;
	std::vector<Light*> lights;
	Controller* controller;
	Skybox* skybox;
	ShaderProgram* defShaderProgram;
	Model* defModel;
	glm::vec3 defColor;
	Texture* defTexture;
	double mouseX = 0;
	double mouseY = 0;
	double scrollY = 0;
	glm::vec3 movementVector = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec2 windowSize = glm::vec2(1600, 900);
	int selectedObjectId = 0;
	int selectedObjectIndex = -1;
	int frameCount = 0;
	Flashlight* flashlight = nullptr;
	int timer = 0;
	BezierSplineTransform* bezierSpline;
	DrawableObject* bezierObject;
};

