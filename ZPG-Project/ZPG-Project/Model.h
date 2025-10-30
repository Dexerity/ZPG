#pragma once

#include <GL/glew.h>

#include <cstddef>
#include <iostream>

#include "tiny_obj_loader.h"

class Model
{
public: 
	Model(const char* name);
	~Model();
	void drawModel();
private:
	GLuint VAO;
	GLuint VBO;
	int vertexCount;
};
