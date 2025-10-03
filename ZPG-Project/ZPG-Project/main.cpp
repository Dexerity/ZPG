#include "Application.h"

int main(void)
{
	Application* app = new Application(800, 600);
	
	app->createShaders();
	app->createModels();
	app->createScenes();

	app->Run();
}