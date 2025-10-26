#include "Application.h"

int main(void)
{
	Application* app = new Application(1600, 900);
	
	app->createShaders();
	app->createModels();
	app->createScenes();

	app->Run();
}