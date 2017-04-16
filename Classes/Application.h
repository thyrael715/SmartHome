#pragma once

#include "Object.h"

class Application
{
public:

	CREATE_FUNC(Application);
	Application();
	~Application();

	void init();
	void run();

private:

	sf::RenderWindow* m_window;
	Object* m_sceneObject;
};