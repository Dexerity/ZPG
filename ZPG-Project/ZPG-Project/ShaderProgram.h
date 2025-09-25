#pragma once

class ShaderProgram
{
public:
	ShaderProgram();
	void applyVertexShader(char* shader);
	void applyFragmentShader(char* shader);

private:
	char* vertexShader = nullptr;
	char* fragmentShader = nullptr;
};

