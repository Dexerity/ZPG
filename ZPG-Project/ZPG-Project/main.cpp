#include "Application.h"e

int main(void)
{
	Application* app = new Application(800, 600);
	
	app->createShaders();
	app->createModels();

	app->Run();
}