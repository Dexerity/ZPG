#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <iostream>

class Texture
{
public:
	Texture(std::string texturePath);
	void bind(GLuint slot);
	void unbind();
private:
	GLuint texID;
	std::string texturePath;
};


