#include "ShaderProgram.h"

class ShaderProgram
{
	ShaderProgram();
	
	void applyVertexShader(char* shader)
	{
		this->vertexShader = shader;
	}
};


