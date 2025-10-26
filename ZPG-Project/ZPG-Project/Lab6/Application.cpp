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

Application::~Application()
{
	for (auto shaderProgram : shaderPrograms)
	{
		delete shaderProgram;
	}
	for (auto model : models)
	{
		delete model;
	}
	for (auto scene : scenes)
	{
		delete scene;
	}

	delete controller;
	delete shader;
	delete window;
}

void Application::Run()
{
	float angle = 0;
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));


	

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scenes[this->controller->getActiveScene() - 1]->drawObjects();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::createShaders()
{
	//Constant
	Shader* constantShader = new Shader();
	constantShader->createShaderFromFile(GL_VERTEX_SHADER, "./Shaders/general.vert");
	constantShader->createShaderFromFile(GL_FRAGMENT_SHADER, "./Shaders/constant.frag");

	//Lambert
	Shader* lambertShader = new Shader();
	lambertShader->createShaderFromFile(GL_VERTEX_SHADER, "./Shaders/general.vert");
	lambertShader->createShaderFromFile(GL_FRAGMENT_SHADER, "./Shaders/lambert.frag");

	//Phong
	Shader* phongShader = new Shader();
	phongShader->createShaderFromFile(GL_VERTEX_SHADER, "./Shaders/general.vert");
	phongShader->createShaderFromFile(GL_FRAGMENT_SHADER, "./Shaders/phong.frag");

	//Blinn-Phong
	Shader* blinnShader = new Shader();
	blinnShader->createShaderFromFile(GL_VERTEX_SHADER, "./Shaders/general.vert");
	blinnShader->createShaderFromFile(GL_FRAGMENT_SHADER, "./Shaders/blinnphong.frag");

	shaderPrograms.push_back(new ShaderProgram(*constantShader));
	shaderPrograms.push_back(new ShaderProgram(*lambertShader));
	shaderPrograms.push_back(new ShaderProgram(*phongShader));
	shaderPrograms.push_back(new ShaderProgram(*blinnShader));




	/*this->shader = new Shader();
	shader->createShaderFromFile(GL_VERTEX_SHADER, "./Shaders/verShader1.txt");
	shader->createShaderFromFile(GL_FRAGMENT_SHADER, "./Shaders/fragShader1.txt");

	shaderPrograms.push_back(new ShaderProgram(*shader));

	this->shader = new Shader();
	shader->createShaderFromFile(GL_VERTEX_SHADER, "./Shaders/verShader2.txt");
	shader->createShaderFromFile(GL_FRAGMENT_SHADER, "./Shaders/fragShader2.txt");

	shaderPrograms.push_back(new ShaderProgram(*shader));
	shaderPrograms.push_back(new ShaderProgram(*shader));*/
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
		1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	   -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,

	   -1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
	   -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f
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
	Transformation* transform = nullptr;

	Camera* cam1 = new Camera();
	std::vector<Light*> lights1;
	lights1.push_back(new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f));

	scenes.push_back(new Scene(this->controller, cam1, lights1));

	std::vector<DrawableObject*> dObjects;

	dObjects.push_back(new DrawableObject(models[3], shaderPrograms[2], glm::vec3(1.0f, 1.0f, 1.0f)));
	dObjects.push_back(new DrawableObject(models[3], shaderPrograms[2], glm::vec3(1.0f, 1.0f, 1.0f)));
	dObjects.push_back(new DrawableObject(models[3], shaderPrograms[2], glm::vec3(1.0f, 1.0f, 1.0f)));
	dObjects.push_back(new DrawableObject(models[3], shaderPrograms[2], glm::vec3(1.0f, 1.0f, 1.0f)));

	transform = new Transformation();
	transform->transforms.push_back(new Translate(glm::vec3(0.5f, 0.0f, 0.0f)));
	transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
	dObjects[0]->addTransform(transform);

	transform = new Transformation();
	transform->transforms.push_back(new Translate(glm::vec3(0.0f, 0.5f, 0.0f)));
	transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
	dObjects[1]->addTransform(transform);

	transform = new Transformation();
	transform->transforms.push_back(new Translate(glm::vec3(-0.5f, 0.0f, 0.0f)));
	transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
	dObjects[2]->addTransform(transform);

	transform = new Transformation();
	transform->transforms.push_back(new Translate(glm::vec3(0.0f, -0.5f, 0.0f)));
	transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
	dObjects[3]->addTransform(transform);

	scenes[0]->addDrawableObjects(dObjects);
	
	////-------------------------------

	Camera* cam2 = new Camera();
	std::vector<Light*> lights2;
	lights2.push_back(new Light(glm::vec3(0.5f, 0.2f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f));

	scenes.push_back(new Scene(this->controller, cam2, lights2));

	std::vector<DrawableObject*> dObjects2;

	dObjects2.push_back(new DrawableObject(models[3], shaderPrograms[2], glm::vec3(1.0f, 1.0f, 1.0f)));

	transform = new Transformation();
	transform->transforms.push_back(new Translate(glm::vec3(0.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
	dObjects2[0]->addTransform(transform);

	scenes[1]->addDrawableObjects(dObjects2);

	////-------------------------------

	//Camera* cam3 = new Camera();
	//std::vector<Light*> lights3;
	//lights3.push_back(new Light(glm::vec3(-0.3f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f));
	//lights3.push_back(new Light(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f));
	//lights3.push_back(new Light(glm::vec3(0.3f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f));


	//scenes.push_back(new Scene(this->controller, cam3, lights3));

	//std::vector<DrawableObject*> dObjects3;

	//dObjects3.push_back(new DrawableObject(models[3], shaderPrograms[2], glm::vec3(1.0f, 1.0f, 1.0f)));

	//transform = new Transformation();
	//transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
	//dObjects3[0]->addTransform(transform);

	//scenes[2]->addDrawableObjects(dObjects3);

	////-------------------------------

	//Camera* cam4 = new Camera();
	//std::vector<Light*> lights4;
	//lights4.push_back(new Light(glm::vec3(-0.3f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f));
	//lights4.push_back(new Light(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f));
	//lights4.push_back(new Light(glm::vec3(0.3f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f));


	//scenes.push_back(new Scene(this->controller, cam4, lights4));

	//std::vector<DrawableObject*> dObjects4;

	//dObjects4.push_back(new DrawableObject(models[3], shaderPrograms[3], glm::vec3(1.0f, 1.0f, 1.0f)));

	//transform = new Transformation();
	//transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
	//dObjects4[0]->addTransform(transform);

	//scenes[3]->addDrawableObjects(dObjects4);
	
	
	
	//Scene 5
	Camera* cam5 = new Camera();
	std::vector<Light*> lights5;


	for (int i = 0; i < 10; i++)
	{
		lights5.push_back(new Light(glm::vec3((rand() % 50 - 50) / 10.0, 0.2f, (rand() % 50 - 50) / 10.0), glm::vec3(1.0f, 1.0f, 0.0f), 1.0f));
		transform = new Transformation();
		transform->transforms.push_back(new RandomTranslate(glm::vec3(3.0f, 0.0f, 3.0f), 60));
		lights5[i]->setTransformation(transform);
	}
	
	
	
	

	scenes.push_back(new Scene(this->controller, cam5, lights5));

	std::vector<DrawableObject*> dObjects5;

	dObjects5.push_back(new DrawableObject(models[5], shaderPrograms[3], glm::vec3(0.0f, 1.0f, 0.0f)));
	transform = new Transformation();
	transform->transforms.push_back(new Scale(glm::vec3(10.0f, 0.0f, 10.0f)));
	dObjects5[0]->addTransform(transform);

	for (int i = 0; i < 256; i++)
	{
		transform = new Transformation();
		if ((i / 16 + i % 16) % 2 == 0)
		{
			dObjects5.push_back(new DrawableObject(models[4], shaderPrograms[3], glm::vec3(0.0f, 1.0f, 0.0f)));
		}
		else
		{
			dObjects5.push_back(new DrawableObject(models[7], shaderPrograms[3], glm::vec3(0.0f, 1.0f, 0.0f)));
		}

		//1,25

		transform->transforms.push_back(new Translate(glm::vec3(-10.0f, 0.0f, 10.0f)));
		transform->transforms.push_back(new Translate(glm::vec3((i % 16) * 1.5f, 0.0f, (i / 16) * -1.5f)));
		transform->transforms.push_back(new Rotate(glm::vec3(0.0f, 1.0f, 0.0f), rand() % 360));
		transform->transforms.push_back(new Scale(glm::vec3(0.4f, 0.4f, 0.4f)));
		dObjects5[i + 1]->addTransform(transform);
	}


	scenes[2]->addDrawableObjects(dObjects5);

}


