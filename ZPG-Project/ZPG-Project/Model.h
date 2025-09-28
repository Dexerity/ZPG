#pragma once

#include <GL/glew.h>

#include <cstddef>

class Model
{
public: 
	Model(float* points, int pointCount);
	int getPointCount();
	void drawModel();
private:
	GLuint VAO;
	GLuint VBO;
	int pointCount;
};
