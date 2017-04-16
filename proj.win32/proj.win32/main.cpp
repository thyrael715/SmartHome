#include <iostream>
#include "Application.h"


int main()
{
	Application* app = Application::create();
	app->run();

	delete app;

	return 0;
}