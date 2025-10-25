#include "Controller.h"




double Controller::mouseX = 0;
double Controller::mouseY = 0;
glm::vec3 Controller::movementVector = glm::vec3(0.0f, 0.0f, 0.0f);
int Controller::activeScene = 1;
int Controller::height = 900;
int Controller::width = 1600;
double Controller::scrollY = 0;

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
	glfwSetScrollCallback(window, scroll_callback);
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

	static bool wPressed = false;
	static bool sPressed = false;
	static bool aPressed = false;
	static bool dPressed = false;
	static bool shiftPressed = false;
	static bool spacePressed = false;

	if (key == GLFW_KEY_W) wPressed = (action != GLFW_RELEASE);
	if (key == GLFW_KEY_S) sPressed = (action != GLFW_RELEASE);
	if (key == GLFW_KEY_A) aPressed = (action != GLFW_RELEASE);
	if (key == GLFW_KEY_D) dPressed = (action != GLFW_RELEASE);
	if (key == GLFW_KEY_LEFT_SHIFT) shiftPressed = (action != GLFW_RELEASE);
	if (key == GLFW_KEY_SPACE) spacePressed = (action != GLFW_RELEASE);


	movementVector.x = (dPressed ? 1.0f : 0.0f) - (aPressed ? 1.0f : 0.0f);
	movementVector.z = (sPressed ? -1.0f : 0.0f) + (wPressed ? 1.0f : 0.0f);
	movementVector.y = (spacePressed ? 0.5f : 0.0f) - (shiftPressed ? 0.5f : 0.0f);


	if(key >= 49 && key <= 57 && action == GLFW_PRESS)
	{
		activeScene = key - 48;
	}
	


	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Controller::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Controller::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Controller::window_size_callback(GLFWwindow* window, int widthW, int heightW) {
	printf("resize %d, %d \n", widthW, heightW);
	glViewport(0, 0, widthW, heightW);

	width = widthW;
	height = heightW;
}

void Controller::cursor_callback(GLFWwindow* window, double x, double y)
{
	mouseX = x;
	mouseY = y;
}

void Controller::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

void Controller::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	scrollY = yoffset;
	printf("scroll_callback [%f,%f]\n", xoffset, yoffset);
}