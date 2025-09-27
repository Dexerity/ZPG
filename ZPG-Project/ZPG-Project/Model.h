#pragma once

#include <GL/glew.h>
#include <cstddef>

class Model
{
public: 
	Model(float* points, int pointCount);
	int getPointCount();
	GLuint getVAO();
private:
	GLuint VAO;
	GLuint VBO;
	int pointCount;
};
