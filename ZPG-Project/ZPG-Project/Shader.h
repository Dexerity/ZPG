#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <cstddef>
#include <iostream>
#include <fstream>


class Shader
{
public:
	Shader();
	void createShader(GLenum shaderType, const char* shaderString);
	void createShaderFromFile(GLenum shaderType, const char* shaderFile);
	void attachShader(GLuint progID);
	
private:
	GLuint vertexShader;
	GLuint fragmentShader;
};
