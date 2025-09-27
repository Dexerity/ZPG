#pragma once

#include "Shader.h"
#include "Model.h"
#include "ShaderProgram.h"

#include <stdio.h>
#include <cstdlib>
#include <GLFW/glfw3.h>

class Application
{
public:
	Application(int width, int height);
	void Run();
	void createShaders();
	void createModels();

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
private:
	GLFWwindow* window = nullptr;
	ShaderProgram* shaderProgram = nullptr;
	Model* model = nullptr;
	Shader* shader = nullptr;
};