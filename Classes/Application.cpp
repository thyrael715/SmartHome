#include "Application.h"
#include "MainLayer.h"



Application::Application()
	: m_window(nullptr)
	, m_sceneObject(nullptr)
{

}


Application::~Application()
{
	SAFE_DELETE(m_sceneObject);
	SAFE_DELETE(m_window);
}


void Application::init()
{
	const unsigned int	windowWidth = 1600;
	const unsigned int	windowHeight = 900;
	const sf::String	windowName = "SmartHome";
	const unsigned int	antialiasLevel = 16;
	const unsigned int	framerateLimit = 40;


	sf::ContextSettings settings;
	settings.antialiasingLevel = antialiasLevel;

	m_window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowName, sf::Style::Default, settings);
	m_window->setFramerateLimit(framerateLimit);

	Defaults::getInstance()->setWindowSize((float)windowWidth, (float)windowHeight);
	
	m_sceneObject = MainLayer::create();
}


void Application::run()
{
	Scheduler* scheduler = Scheduler::getInstance();

	sf::Clock clock;
	sf::Event event;

	while (m_window->isOpen())
	{
		while (m_window->pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					m_window->close();
					break;
				}
				case sf::Event::MouseButtonPressed:
				case sf::Event::MouseButtonReleased:
				{
					EventDispatcher::getInstance()->triggerEventHandling(event);
					break;
				}
			}
		}

		scheduler->update(clock.getElapsedTime().asSeconds());

		clock.restart();
		
		// draw...
		m_window->clear();
		m_window->draw(*m_sceneObject);
		m_window->display();
	}
}