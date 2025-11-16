#pragma once

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "ShaderProgram.h"
#include "Camera.h"

using namespace std;

class Skybox
{
public:
	Skybox(std::vector<string> sides);
	//void setCamera(Camera* camera);
	void draw(glm::mat4 view, glm::mat4 projection);
	~Skybox();
private:
	ShaderProgram* shaderProgram;
	GLuint VBO, VAO;
	GLuint textureID;
};

