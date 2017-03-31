#include <SFML/Graphics.hpp>
#include "Background.h"
#include "CentralPanel.h"
#include "Defaults.h"
#include "Scheduler.h"
#include <iostream>


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(1600, 900), "SmartHome", sf::Style::Default, settings);

	Defaults::getInstance()->setWindowSize((float)window.getSize().x, (float)window.getSize().y);
	auto scheduler = Scheduler::getInstance();


	Background* bg = new Background();
	CentralPanel *cp = new CentralPanel();

	cp->setPosition(800, 450);

	window.setFramerateLimit(60);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		
		sf::Time deltaTime = clock.getElapsedTime();

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					window.close();
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

		scheduler->update(deltaTime.asMilliseconds());

		clock.restart().asMilliseconds();


		// draw...
		window.clear();


		window.draw(*bg);
		window.draw(*cp);

		// end the current frame
		window.display();
	}



	return 0;
}