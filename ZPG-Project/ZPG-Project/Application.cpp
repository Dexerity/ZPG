#include "Application.h"

int Application::activeScene = 1;

Application::Application(int width, int height)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();

	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
}

void Application::Run()
{
	float angle = 0;
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));


	Transformation *transform = new Transformation();
	transform->transforms.push_back(new Translate(glm::vec3(0.1f, 0.1f, 0.0f)));
	transform->transforms.push_back(new Scale(glm::vec3(1.0f, 1.5f, 1.0f)));
	transform->transforms.push_back(new Rotate(glm::vec3(0.0f, 0.0f, 1.0f), 45.0f));
	this->scenes[1]->dObjects[0]->addTransform(transform);


	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scenes[activeScene - 1]->drawObjects();

		/*angle += 0.1;
		M = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
		shaderPrograms[1]->setUniform("modelMatrix", M);*/


		//shaderPrograms[2]->applyShaderProgram();
		//models[2]->drawModel();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::createShaders()
{
	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vc;"
		"out vec3 color;"
		"void main () {"
		"	  color = vc;"
		"     gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 330\n"
		"in vec3 color;"
		"out vec4 fragColor;"
		"void main () {"
		"	  fragColor = vec4 (1.0, 0.0, 0.0, 1.0);"
		"     fragColor = vec4 (color, 1.0);"
		"}";

	this->shader = new Shader(vertex_shader, fragment_shader);

	shaderPrograms.push_back(new ShaderProgram(*shader));

	const char* vertex_shader2 =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vc;"
		"uniform mat4 modelMatrix;"
		"out vec3 color;"
		"void main () {"
		"	  color = vc;"
		"     gl_Position = modelMatrix * vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader2 =
		"#version 330\n"
		"in vec3 color;"
		"out vec4 fragColor;"
		"void main () {"
		"    fragColor = vec4(1.0, 0.0, 0.0, 1.0);"
		"    fragColor = vec4 (color, 1.0);"
		"}";

	this->shader = new Shader(vertex_shader2, fragment_shader2);

	shaderPrograms.push_back(new ShaderProgram(*shader));

	const char* vertex_shader3 =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vc;"
		"out vec3 color;"
		"void main () {"
		"	  color = vc;"
		"     gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader3 =
		"#version 330\n"
		"in vec3 color;"
		"out vec4 fragColor;"
		"void main () {"
		"	  fragColor = vec4 (1.0, 1.0, 0.0, 0.5);"
		"}";

	this->shader = new Shader(vertex_shader3, fragment_shader3);

	shaderPrograms.push_back(new ShaderProgram(*shader));

}

void Application::createModels()
{
	float hexagon[] = {
		0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.87f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,

		0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		-0.87f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		-0.87f,-0.5f, 0.0f,   0.0f, 0.0f, 1.0f,

		0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		-0.87f,-0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
		0.0f, -1.0f, 0.0f,   1.0f, 1.0f, 0.0f,

		0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.0f, -1.0f, 0.0f,   1.0f, 1.0f, 0.0f,
		0.87f,-0.5f, 0.0f,   0.0f, 1.0f, 1.0f,

		0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.87f,-0.5f, 0.0f,   0.0f, 1.0f, 1.0f,
		0.87f, 0.5f, 0.0f,   1.0f, 0.0f, 1.0f, 

		0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.87f, 0.5f, 0.0f,   1.0f, 0.0f, 1.0f,
		0.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f
	};

	float triangle[] = {
		-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
	};

	float square[] = {
		0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f
	};

	models.push_back(new Model(hexagon, sizeof(hexagon) / sizeof(float)));
	models.push_back(new Model(triangle, sizeof(triangle) / sizeof(float)));
	models.push_back(new Model(square, sizeof(square) / sizeof(float)));
}

void Application::createScenes()
{
	scenes.push_back(new Scene());
	scenes[0]->dObjects.push_back(new DrawableObject(models[0], shaderPrograms[1]));

	scenes.push_back(new Scene());
	scenes[1]->dObjects.push_back(new DrawableObject(models[1], shaderPrograms[1]));

	scenes.push_back(new Scene());
	scenes[2]->dObjects.push_back(new DrawableObject(models[2], shaderPrograms[1]));
}

void Application::error_callback(int error, const char* description) { fputs(description, stderr); }

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		activeScene = 1;
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		activeScene = 2;
	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
		activeScene = 3;
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Application::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Application::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}