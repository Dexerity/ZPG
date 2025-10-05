#pragma once

#include <GL/glew.h>

#include <cstddef>

class Model
{
public: 
	Model(const float* points, int pointCount);
	void drawModel();
private:
	GLuint VAO;
	GLuint VBO;
	int pointCount;
};
