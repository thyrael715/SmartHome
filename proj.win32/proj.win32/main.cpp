#include <SFML/Graphics.hpp>
#include "Background.h"
#include "CentralPanel.h"
#include "Defaults.h"

#include <iostream>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SmartHome", sf::Style::Default, settings);

	Defaults::getInstance()->setWindowSize((float)window.getSize().x, (float)window.getSize().y);
	
	Background* bg = Background::create();
	CentralPanel *cp = CentralPanel::create();
	window.setFramerateLimit(60);
	
	while (window.isOpen())
	{
		window.clear();

		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					window.close();
					break;
				}
			}
		}

		bg->draw(window);
		cp->draw(window);

		window.display();
	}

	return 0;
}