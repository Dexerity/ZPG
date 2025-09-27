#pragma once

#include <GL/glew.h>
#include <cstddef>

class Model
{
public: 
	Model(float* points, int pointCount);
	GLuint getVAO();
private:
	GLuint VAO;
	GLuint VBO;
};
