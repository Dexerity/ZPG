#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstddef>

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