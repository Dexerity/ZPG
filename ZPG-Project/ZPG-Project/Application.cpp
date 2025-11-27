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

	const float texPlain[] = {
		//vrchol, normála, uv souřadnice
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

	   -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f
	};

    //models.push_back(new Model(hexagon, sizeof(hexagon) / sizeof(float)));       // 0: hexagon
    //models.push_back(new Model(triangle, sizeof(triangle) / sizeof(float)));     // 1: triangle
    //models.push_back(new Model(square, sizeof(square) / sizeof(float)));         // 2: square
    //models.push_back(new Model(sphere, sizeof(sphere) / sizeof(float)));         // 3: sphere
    //models.push_back(new Model(tree, sizeof(tree) / sizeof(float)));             // 4: tree
    //models.push_back(new Model(plain2, sizeof(plain2) / sizeof(float)));           // 5: plain
    //models.push_back(new Model(gift, sizeof(gift) / sizeof(float)));             // 6: gift
    //models.push_back(new Model(bushes, sizeof(bushes) / sizeof(float)));         // 7: bushes
    //models.push_back(new Model(suziFlat, sizeof(suziFlat) / sizeof(float)));     // 8: suziFlat
    //models.push_back(new Model(suziSmooth, sizeof(suziSmooth) / sizeof(float))); // 9: suziSmooth
	//models.push_back(new Model("Cottage_obj.obj"));
	models.push_back(new Model(texPlain, sizeof(texPlain) / sizeof(float) / 8, true));
	models.push_back(new Model("teren.obj"));
	models.push_back(new Model("teren.obj"));
	models.push_back(new Model("teren.obj"));
	models.push_back(new Model("Lowpoly_tree_sample.obj"));
	models.push_back(new Model("Lowpoly_tree_sample.obj"));
	//models.push_back(new Model("forrest.obj"));
	//models.push_back(new Model("eyeball.obj"));
	models.push_back(new Model("13913_Sun_v2_l3.obj"));
	models.push_back(new Model("login.obj"));
}

void Application::createScenes()
{
	Transformation* transform = nullptr;

	/*Camera* cam1 = new Camera();
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

	scenes[0]->addDrawableObjects(dObjects);*/
	
	////-------------------------------

	Camera* cam2 = new Camera();
	std::vector<Light*> lights2;
	lights2.push_back(new Light(glm::vec3(0.3f, 0.2f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f));
	//lights2.push_back(new DirectionLight(glm::vec3(0.5f, 0.2f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, glm::vec3(0.0f, -1.0f, 3.0f)));
	
	std::vector<std::string> skySides = {
	"Assets/Skybox/posx.jpg",
	"Assets/Skybox/negx.jpg",
	"Assets/Skybox/posy.jpg",
	"Assets/Skybox/negy.jpg",
	"Assets/Skybox/posz.jpg",
	"Assets/Skybox/negz.jpg"
	};
	Skybox* skybox1 = new Skybox(skySides);

	scenes.push_back(new Scene(this->controller, cam2, lights2, skybox1));

	std::vector<DrawableObject*> dObjects2;

	dObjects2.push_back(new DrawableObject(models[1], shaderPrograms[3], glm::vec3(-1.0f, -1.0f, -1.0f), new Texture("Assets/wooden_fence.png")));

	dObjects2.push_back(new DrawableObject(models[3], shaderPrograms[3], glm::vec3(-1.0f), new Texture("Assets/grass.png")));
	dObjects2.push_back(new DrawableObject(models[3], shaderPrograms[3], glm::vec3(-1.0f), new Texture("Assets/grass.png")));

	glm::mat4 customMat = glm::mat4(1.0f);
	customMat[3][3] = 20.0f;

	transform = new Transformation();
	transform->transforms.push_back(new CustomTransform(customMat));
	transform->transforms.push_back(new Translate(glm::vec3(0.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new Scale(glm::vec3(0.04f, 0.04f, 0.04f)));
	dObjects2[1]->addTransform(transform);

	transform = new Transformation();
	transform->transforms.push_back(new Translate(glm::vec3(0.5f, 0.0f, 0.0f)));
	transform->transforms.push_back(new Scale(glm::vec3(0.04f, 0.04f, 0.04f)));
	dObjects2[2]->addTransform(transform);

	scenes[0]->addDrawableObjects(dObjects2);

	////-------------------------------

	Camera* cam3 = new Camera();
	std::vector<Light*> lights3;
	lights3.push_back(new DirectionLight(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1, glm::vec3(0.3f, -1.0f, 0.0f)));

	scenes.push_back(new Scene(this->controller, cam3, lights3, skybox1, 1));

	scenes[1]->addAObject(shaderPrograms[2], models[5], glm::vec3(-1.f), new Texture("Assets/Eye_D.jpg"));

	std::vector<DrawableObject*> dObjects3;

	dObjects3.push_back(new DrawableObject(models[2], shaderPrograms[2], glm::vec3(-1.f), new Texture("Assets/grass.png")));
	dObjects2[0]->addMaterial(new Material(0.1f, 1.0f, 1.0f, 1.0f));


	for (int i = 0; i < 16; i++)
	{
		transform = new Transformation();
		dObjects3.push_back(new DrawableObject(models[4], shaderPrograms[2], glm::vec3(0.0f, 1.0f, 0.0f)));
		dObjects3[i + 1]->addMaterial(new Material(0.1f, 0.9f, 0.05f, 1.0f));

		//1,25

		transform->transforms.push_back(new Translate(glm::vec3(-40.0f, 0.0f, 40.0f)));
		transform->transforms.push_back(new Translate(glm::vec3((i % 4) * 20.0f, 0.0f, (i / 4) * -20.0f)));
		//transform->transforms.push_back(new Rotate(glm::vec3(0.0f, 1.0f, 0.0f), rand() % 360));
		transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
		dObjects3[i + 1]->addTransform(transform);
	}

	/*transform = new Transformation();
	transform->transforms.push_back(new Scale(glm::vec3(0.08f, 0.08f, 0.08f)));

	dObjects3.push_back(new DrawableObject(models[4], shaderPrograms[2], glm::vec3(0.0f, 1.0f, 0.0f)));
	dObjects3[1]->addTransform(transform);*/

	scenes[1]->addDrawableObjects(dObjects3);

	////-------------------------------

	Camera* cam4 = new Camera();
	std::vector<Light*> lights4;
	lights4.push_back(new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f));
	lights4[0]->k_c = 1.0f;
	lights4[0]->k_l = 0.001f;
	lights4[0]->k_q = 0.000001f;

	std::vector<std::string> skySides2 = {
		"Assets/SkyboxSpace/sky.jpg",
		"Assets/SkyboxSpace/sky.jpg",
		"Assets/SkyboxSpace/sky.jpg",
		"Assets/SkyboxSpace/sky.jpg",
		"Assets/SkyboxSpace/sky.jpg",
		"Assets/SkyboxSpace/sky.jpg"
	};
	Skybox* skybox2 = new Skybox(skySides2);

	scenes.push_back(new Scene(this->controller, cam4, lights4, skybox2, 0));

	std::vector<DrawableObject*> dObjects4;
	dObjects4.push_back(new DrawableObject(models[6], shaderPrograms[3], glm::vec3(-1.f), new Texture("Assets/2K_sun.jpg")));
	dObjects4[0]->addMaterial(new Material(1.0f, 0.0f, 0.0f, 1.0f));
	dObjects4.push_back(new DrawableObject(models[6], shaderPrograms[3], glm::vec3(-1.f), new Texture("Assets/2K_mercury.jpg")));
	dObjects4[1]->addMaterial(new Material(0.1f, 0.9f, 0.05f, 4.0f));
	dObjects4.push_back(new DrawableObject(models[6], shaderPrograms[3], glm::vec3(-1.f), new Texture("Assets/2K_venus_surface.jpg")));
	dObjects4[2]->addMaterial(new Material(0.1f, 0.9f, 0.05f, 4.0f));
	dObjects4.push_back(new DrawableObject(models[6], shaderPrograms[3], glm::vec3(-1.f), new Texture("Assets/2k_earth_daymap.jpg")));
	dObjects4[3]->addMaterial(new Material(0.1f, 1.0f, 0.3f, 32.0f));
	dObjects4.push_back(new DrawableObject(models[6], shaderPrograms[3], glm::vec3(-1.f), new Texture("Assets/2k_moon.jpg")));
	dObjects4[4]->addMaterial(new Material(0.1f, 0.9f, 0.05f, 4.0f));
	dObjects4.push_back(new DrawableObject(models[6], shaderPrograms[3], glm::vec3(-1.f), new Texture("Assets/2k_mars.jpg")));
	dObjects4[5]->addMaterial(new Material(0.1f, 0.9f, 0.05f, 4.0f));
	dObjects4.push_back(new DrawableObject(models[6], shaderPrograms[3], glm::vec3(-1.f), new Texture("Assets/2k_jupiter.jpg")));
	dObjects4[6]->addMaterial(new Material(0.1f, 0.9f, 0.05f, 4.0f));
	dObjects4.push_back(new DrawableObject(models[6], shaderPrograms[3], glm::vec3(-1.f), new Texture("Assets/2k_saturn.jpg")));
	dObjects4[7]->addMaterial(new Material(0.1f, 0.9f, 0.05f, 4.0f));
	dObjects4.push_back(new DrawableObject(models[6], shaderPrograms[3], glm::vec3(-1.f), new Texture("Assets/2k_uranus.jpg")));
	dObjects4[8]->addMaterial(new Material(0.1f, 0.9f, 0.05f, 4.0f));
	dObjects4.push_back(new DrawableObject(models[6], shaderPrograms[3], glm::vec3(-1.f), new Texture("Assets/2k_neptune.jpg")));
	dObjects4[9]->addMaterial(new Material(0.1f, 0.9f, 0.05f, 4.0f));
	dObjects4.push_back(new DrawableObject(models[7], shaderPrograms[3], glm::vec3(-1.f), new Texture("Assets/2k_neptune.jpg")));
	dObjects4[9]->addMaterial(new Material(0.1f, 0.9f, 0.05f, 4.0f));

	//SUN
	transform = new Transformation();
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 13.52f));
	transform->transforms.push_back(new Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f));
	transform->transforms.push_back(new Scale(glm::vec3(0.002f, 0.002f, 0.002f)));
	dObjects4[0]->addTransform(transform);

	//MERCURY
	transform = new Transformation();
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.415f));
	transform->transforms.push_back(new Translate(glm::vec3(3.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 6.22f));
	transform->transforms.push_back(new Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f));
	transform->transforms.push_back(new Scale(glm::vec3(0.0004f, 0.0004f, 0.0004f)));
	dObjects4[1]->addTransform(transform);

	//VENUS
	transform = new Transformation();
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.162f));
	transform->transforms.push_back(new Translate(glm::vec3(5.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 1.5f));
	transform->transforms.push_back(new Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f));
	transform->transforms.push_back(new Scale(glm::vec3(0.0009f, 0.0009f, 0.0009f)));
	dObjects4[2]->addTransform(transform);

	//EARTH
	transform = new Transformation();
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.1f));
	transform->transforms.push_back(new Translate(glm::vec3(10.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 365.0f));
	transform->transforms.push_back(new Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f));
	transform->transforms.push_back(new Scale(glm::vec3(0.0008f, 0.0008f, 0.0008f)));
	dObjects4[3]->addTransform(transform);

	//MOON
	transform = new Transformation();
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.1f));
	transform->transforms.push_back(new Translate(glm::vec3(10.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 13.52f));
	transform->transforms.push_back(new Translate(glm::vec3(1.5f, 0.0f, 0.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.01f));
	transform->transforms.push_back(new Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f));
	transform->transforms.push_back(new Scale(glm::vec3(0.0002f, 0.0002f, 0.0002f)));
	dObjects4[4]->addTransform(transform);

	//LOGIN
	transform = new Transformation();
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.1f));
	transform->transforms.push_back(new Translate(glm::vec3(10.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), -13.52f));
	transform->transforms.push_back(new Translate(glm::vec3(2.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.01f));
	//transform->transforms.push_back(new Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f));
	transform->transforms.push_back(new Scale(glm::vec3(0.2f, 0.2f, 0.2f)));
	dObjects4[10]->addTransform(transform);

	//MARS
	transform = new Transformation();
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.053f));
	transform->transforms.push_back(new Translate(glm::vec3(15.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 350.4f));
	transform->transforms.push_back(new Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f));
	transform->transforms.push_back(new Scale(glm::vec3(0.0007f, 0.0007f, 0.0007f)));
	dObjects4[5]->addTransform(transform);

	//JUPITER
	transform = new Transformation();
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.0084f));
	transform->transforms.push_back(new Translate(glm::vec3(25.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 876.0f));
	transform->transforms.push_back(new Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f));
	transform->transforms.push_back(new Scale(glm::vec3(0.007f, 0.007f, 0.007f)));
	dObjects4[6]->addTransform(transform);

	//SATURN
	transform = new Transformation();
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.0034f));
	transform->transforms.push_back(new Translate(glm::vec3(35.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 796.3f));
	transform->transforms.push_back(new Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f));
	transform->transforms.push_back(new Scale(glm::vec3(0.006f, 0.006f, 0.006f)));
	dObjects4[7]->addTransform(transform);

	//URANUS
	transform = new Transformation();
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.0014f));
	transform->transforms.push_back(new Translate(glm::vec3(45.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 515.3f));
	transform->transforms.push_back(new Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f));
	transform->transforms.push_back(new Scale(glm::vec3(0.0025f, 0.0025f, 0.0025f)));
	dObjects4[8]->addTransform(transform);

	//NEPTUNE
	transform = new Transformation();
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.0008f));
	transform->transforms.push_back(new Translate(glm::vec3(55.0f, 0.0f, 0.0f)));
	transform->transforms.push_back(new DynamicRotate(glm::vec3(0.0f, 1.0f, 0.0f), 547.5f));
	transform->transforms.push_back(new Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 90.0f));
	transform->transforms.push_back(new Scale(glm::vec3(0.0024f, 0.0024f, 0.0024f)));
	dObjects4[9]->addTransform(transform);


	scenes[2]->addDrawableObjects(dObjects4);




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
	
	
	
	////Scene 5
	//Camera* cam5 = new Camera();
	//std::vector<Light*> lights5;


	//for (int i = 0; i < 10; i++)
	//{
	//	lights5.push_back(new Light(glm::vec3((rand() % 50 - 50) / 10.0, 0.2f, (rand() % 50 - 50) / 10.0), glm::vec3(1.0f, 1.0f, 0.0f), 1.0f));
	//	transform = new Transformation();
	//	transform->transforms.push_back(new RandomTranslate(glm::vec3(3.0f, 0.0f, 3.0f), 60));
	//	lights5[i]->setTransformation(transform);
	//}
	//
	//
	//
	//

	//scenes.push_back(new Scene(this->controller, cam5, lights5));

	//std::vector<DrawableObject*> dObjects5;

	//dObjects5.push_back(new DrawableObject(models[5], shaderPrograms[3], glm::vec3(0.0f, 1.0f, 0.0f)));
	//transform = new Transformation();
	//transform->transforms.push_back(new Scale(glm::vec3(10.0f, 0.0f, 10.0f)));
	//dObjects5[0]->addTransform(transform);

	//for (int i = 0; i < 256; i++)
	//{
	//	transform = new Transformation();
	//	if ((i / 16 + i % 16) % 2 == 0)
	//	{
	//		dObjects5.push_back(new DrawableObject(models[4], shaderPrograms[3], glm::vec3(0.0f, 1.0f, 0.0f)));
	//	}
	//	else
	//	{
	//		dObjects5.push_back(new DrawableObject(models[7], shaderPrograms[3], glm::vec3(0.0f, 1.0f, 0.0f)));
	//	}

	//	//1,25

	//	transform->transforms.push_back(new Translate(glm::vec3(-10.0f, 0.0f, 10.0f)));
	//	transform->transforms.push_back(new Translate(glm::vec3((i % 16) * 1.5f, 0.0f, (i / 16) * -1.5f)));
	//	transform->transforms.push_back(new Rotate(glm::vec3(0.0f, 1.0f, 0.0f), rand() % 360));
	//	transform->transforms.push_back(new Scale(glm::vec3(0.4f, 0.4f, 0.4f)));
	//	dObjects5[i + 1]->addTransform(transform);
	//}


	//scenes[2]->addDrawableObjects(dObjects5);

}


