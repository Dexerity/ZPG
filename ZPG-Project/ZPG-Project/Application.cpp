#include "Application.h"

int Application::activeScene = 1;
int Application::height = 900;
int Application::width = 1600;

Application::Application(int width, int height)
{
	this->width = width;
	this->height = height;

	//glfwSetErrorCallback(error_callback);
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

	this->controller = new Controller(window);
}

void Application::Run()
{
	float angle = 0;
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));


	

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scenes[activeScene - 1]->drawObjects();

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
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"out vec3 color;"
		"void main () {"
		"	  color = vc;"
		"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 330\n"
		"in vec3 color;"
		"out vec4 fragColor;"
		"void main () {"
		"	  fragColor = vec4 (1.0, 0.0, 0.0, 1.0);"
		"}";

	this->shader = new Shader(vertex_shader, fragment_shader);

	shaderPrograms.push_back(new ShaderProgram(*shader));

	const char* vertex_shader2 =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vc;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"out vec3 color;"
		"void main () {"
		"	  color = vc;"
		"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
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
		"uniform mat4 modelMatrix;"
		"out vec3 color;"
		"void main () {"
		"	  color = vc;"
		"     gl_Position = modelMatrix * vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader3 =
		"#version 330\n"
		"in vec3 color;"
		"out vec4 fragColor;"
		"void main () {"
		"	  fragColor = vec4 (0.67, 1.0, 1.0, 1.0);"
		"}";

	this->shader = new Shader(vertex_shader3, fragment_shader3);

	shaderPrograms.push_back(new ShaderProgram(*shader));

}

void Application::createModels()
{
	const float hexagon[] = {
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

	const float triangle[] = {
		-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
   0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
   0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
	};

	const float square[] = {
		0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f
	};

	const float plain2[] = {
		1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	   -1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0.0f,
	   -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f
	};

    models.push_back(new Model(hexagon, sizeof(hexagon) / sizeof(float)));       // 0: hexagon
    models.push_back(new Model(triangle, sizeof(triangle) / sizeof(float)));     // 1: triangle
    models.push_back(new Model(square, sizeof(square) / sizeof(float)));         // 2: square
    models.push_back(new Model(sphere, sizeof(sphere) / sizeof(float)));         // 3: sphere
    models.push_back(new Model(tree, sizeof(tree) / sizeof(float)));             // 4: tree
    models.push_back(new Model(plain2, sizeof(plain2) / sizeof(float)));           // 5: plain
    models.push_back(new Model(gift, sizeof(gift) / sizeof(float)));             // 6: gift
    models.push_back(new Model(bushes, sizeof(bushes) / sizeof(float)));         // 7: bushes
    models.push_back(new Model(suziFlat, sizeof(suziFlat) / sizeof(float)));     // 8: suziFlat
    models.push_back(new Model(suziSmooth, sizeof(suziSmooth) / sizeof(float))); // 9: suziSmooth
}

void Application::createScenes()
{
	//Scene 1
	scenes.push_back(new Scene(this->controller));
	scenes[0]->dObjects.push_back(new DrawableObject(models[1], shaderPrograms[0]));

	Transformation* transform = new Transformation();
	/*transform->transforms.push_back(new Translate(glm::vec3(-0.2f, 0.3f, 0.0f)));
	transform->transforms.push_back(new Scale(glm::vec3(0.8f, 0.5f, 1.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 0.0f, 1.0f), 0.5f));
	this->scenes[0]->dObjects[0]->addTransform(transform);*/


	//Scene 2
	scenes.push_back(new Scene(this->controller));
	scenes[1]->dObjects.push_back(new DrawableObject(models[3], shaderPrograms[1]));
	scenes[1]->dObjects.push_back(new DrawableObject(models[3], shaderPrograms[1]));
	scenes[1]->dObjects.push_back(new DrawableObject(models[3], shaderPrograms[1]));
	scenes[1]->dObjects.push_back(new DrawableObject(models[3], shaderPrograms[1]));

	transform = new Transformation();
	transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 1.0f)));
	transform->transforms.push_back(new Translate(glm::vec3(0.0f, 5.0f, 0.0f)));
	this->scenes[1]->dObjects[0]->addTransform(transform);

	transform = new Transformation();
	transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 1.0f)));
	transform->transforms.push_back(new Translate(glm::vec3(5.0f, 0.0f, 0.0f)));
	this->scenes[1]->dObjects[1]->addTransform(transform);
	
	transform = new Transformation();
	transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 1.0f)));
	transform->transforms.push_back(new Translate(glm::vec3(0.0f, -5.0f, 0.0f)));
	this->scenes[1]->dObjects[2]->addTransform(transform);

	transform = new Transformation();
	transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 1.0f)));
	transform->transforms.push_back(new Translate(glm::vec3(-5.0f, 0.0f, 0.0f)));
	this->scenes[1]->dObjects[3]->addTransform(transform);

	
	//Scene 3
	scenes.push_back(new Scene(this->controller));
	scenes[2]->dObjects.push_back(new DrawableObject(models[5], shaderPrograms[2]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[4], shaderPrograms[1]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[4], shaderPrograms[1]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[4], shaderPrograms[1]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[4], shaderPrograms[1]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[4], shaderPrograms[1]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[5], shaderPrograms[1]));

	transform = new Transformation();
	transform->transforms.push_back(new Translate(glm::vec3(0.0f, 0.0f, 0.9f)));
	this->scenes[2]->dObjects[0]->addTransform(transform);

	for (int i = 0; i < 5; i++)
	{
		transform = new Transformation();
		transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 1.0f)));
		transform->transforms.push_back(new Translate(glm::vec3(-8.0f + (i * 4.0f), 0.0f, 0.0f)));
		this->scenes[2]->dObjects[i + 1]->addTransform(transform);
	}

	transform = new Transformation();
	transform->transforms.push_back(new Scale(glm::vec3(1.0f, 0.5f, 1.0f)));
	transform->transforms.push_back(new Translate(glm::vec3(0.0f, -1.0f, 0.5f)));
	this->scenes[2]->dObjects[6]->addTransform(transform);

	scenes[2]->dObjects.push_back(new DrawableObject(models[7], shaderPrograms[0]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[7], shaderPrograms[0]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[7], shaderPrograms[0]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[7], shaderPrograms[0]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[7], shaderPrograms[0]));

	for (int i = 0; i < 5; i++)
	{
		transform = new Transformation();
		transform->transforms.push_back(new Scale(glm::vec3(0.5f, 0.5f, 1.0f)));
		transform->transforms.push_back(new Translate(glm::vec3(-1.6f + (i * 0.8f), -0.2f, 0.0f)));
		this->scenes[2]->dObjects[i + 7]->addTransform(transform);
	}

	scenes[2]->dObjects.push_back(new DrawableObject(models[8], shaderPrograms[1]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[9], shaderPrograms[1]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[8], shaderPrograms[1]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[9], shaderPrograms[1]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[8], shaderPrograms[1]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[9], shaderPrograms[1]));
	scenes[2]->dObjects.push_back(new DrawableObject(models[8], shaderPrograms[1]));

	float yOffset = 0.2;
	for (int i = 0; i < 7; i++)
	{
		transform = new Transformation();
		transform->transforms.push_back(new Translate(glm::vec3(-0.75f + (i * 0.25f), -0.6f + yOffset, 0.0f)));
		transform->transforms.push_back(new Rotate(glm::vec3(0.0f, 1.0f, 0.0f), 180));
		transform->transforms.push_back(new Scale(glm::vec3(0.15f, 0.15f, 0.2f)));
		this->scenes[2]->dObjects[i + 12]->addTransform(transform);
		yOffset *= -1;
	}


}


