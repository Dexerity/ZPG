#pragma once

#include "Shader.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Scene.h"
#include "Controller.h"

#include "Transformation.h"
#include "Translate.h"
#include "Rotate.h"
#include "Scale.h"
#include "DynamicRotate.h"

#include "Models/sphere.h"
#include "Models/tree.h"
#include "Models/plain.h"
#include "Models/gift.h"
#include "Models/bushes.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"

#include <stdio.h>
#include <cstdlib>
#include <vector>

#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class Application
{
public:
	Application(int width, int height);
	~Application();
	void Run();
	void createShaders();
	void createModels();
	void createScenes();

private:
	GLFWwindow* window = nullptr;
	std::vector<ShaderProgram*> shaderPrograms;
	std::vector<Model*> models;
	std::vector<Scene*> scenes;
	Shader* shader = nullptr;
	static int activeScene;
	static int width, height;
	Controller* controller = nullptr;
};