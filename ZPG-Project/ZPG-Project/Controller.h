#pragma once

#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

#include <stdio.h>
#include <cstdlib>

#include "Subject.h"

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
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	double getMouseX() { return mouseX; }
	double getMouseY() { return mouseY; }
	double getScrollY() { return scrollY; }
	void resetScrollY() { scrollY = 0; }
	glm::vec3 getMovementVector() { return movementVector * 0.1f; }
	int getActiveScene() { return activeScene; }
	glm::vec2 getWindowSize() { return glm::vec2(width, height); }
	bool wasClicked(int button);
	void resetClicks();
private:
	static double mouseX, mouseY;
	static double scrollY;
	static glm::vec3 movementVector;
	static int height, width;
	static int activeScene;
	static bool mouseClicked[3];
	static bool deleteClicked;
};

