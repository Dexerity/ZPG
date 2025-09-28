#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <cstddef>
#include <iostream>

class Shader
{
public:
	Shader(const char* vertexString, const char* fragmentString);
	GLuint getVertexShader();
	GLuint getFragmentShader();
	
private:
	GLuint vertexShader;
	GLuint fragmentShader;
};