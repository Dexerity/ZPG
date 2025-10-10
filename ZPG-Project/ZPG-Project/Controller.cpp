#include "Controller.h"




double Controller::mouseX = 0;
double Controller::mouseY = 0;
glm::vec3 Controller::movementVector = glm::vec3(0.0f, 0.0f, 0.0f);

Controller::Controller(GLFWwindow* window)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
}

void Controller::error_callback(int error, const char* description) { fputs(description, stderr); }

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	/*if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		activeScene = 1;
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		activeScene = 2;
	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
		activeScene = 3;*/

	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
		{
			movementVector.z = 1.0f;
		}
		else if (key == GLFW_KEY_S)
		{
			movementVector.z = -1.0f;
		}
		
		
		if (key == GLFW_KEY_A)
		{
			movementVector.x = -1.0f;
		}
		else if (key == GLFW_KEY_D)
		{
			movementVector.x = 1.0f;
		}
	}
	else
	{
		movementVector.x = 0.0f;
		movementVector.z = 0.0f;
	}

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Controller::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Controller::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Controller::window_size_callback(GLFWwindow* window, int widthW, int heightW) {
	printf("resize %d, %d \n", widthW, heightW);
	glViewport(0, 0, widthW, heightW);
}

void Controller::cursor_callback(GLFWwindow* window, double x, double y)
{
	mouseX = x;
	mouseY = y;
}

void Controller::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}