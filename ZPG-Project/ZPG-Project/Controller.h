#pragma once

#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

#include <stdio.h>
#include <cstdlib>

class Controller
{
public:
	Controller(GLFWwindow* window);
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
	double getMouseX() { return mouseX; }
	double getMouseY() { return mouseY; }
	glm::vec3 getMovementVector() { return movementVector * 0.1f; }
	int getActiveScene() { return activeScene; }
private:
	static double mouseX, mouseY;
	static glm::vec3 movementVector;
	static int activeScene;
};

