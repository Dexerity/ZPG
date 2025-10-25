#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Camera.h"
#include "Light.h"

#include <sstream>

class DrawableObject : public Observer
{
public:
	DrawableObject(Model* model, ShaderProgram* shaderProgram, glm::vec3 color);
	~DrawableObject();
	void addSubjects(Camera* camera, std::vector<Light*> lights);
	void addTransform(Transformation* transform);
	void DrawObject();
	void Notify(enum SubjectType type) override;


private:
	Camera* camera = nullptr;
	std::vector<Light*> lights;
	Model* model = nullptr;
	ShaderProgram* shaderProgram = nullptr;
	Transformation* transformation;
	glm::vec3 color;
};

