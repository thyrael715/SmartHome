// ***** Includes *****

#include "BackgroundLayer.h"
#include "Defaults.h"
#include <iostream>


// ***** Defines *****

#define BG_SIZE_OF_HEXAGON			20
#define BG_THICKNESS_OF_HEXAGON		1
#define BG_SIZE_OF_GRADIENT			250

#define COLOR_HEXAGON				sf::Color(40, 40, 40, 255)
#define COLOR_GRADIENT				sf::Color(0, 0, 0, 200)


// ***** Function definitions *****

BackgroundLayer::BackgroundLayer()
	: gradientVertices(nullptr)
{

}


BackgroundLayer::~BackgroundLayer()
{

}


void BackgroundLayer::init()
{
	createHexaGrid();
	createGradientForGrid();
}


void BackgroundLayer::createHexaGrid()
{
	unsigned shiftX = static_cast<unsigned>((sqrt(3) * (BG_SIZE_OF_HEXAGON / 2)) + BG_THICKNESS_OF_HEXAGON);
	unsigned shiftY = static_cast<unsigned>((0.75 * BG_SIZE_OF_HEXAGON) + BG_THICKNESS_OF_HEXAGON);

	for (size_t i = 0; i < WINDOW_HEIGHT / shiftY; i++)
	{
		for (size_t j = 0; j < WINDOW_WIDTH / shiftX; j++)
		{
			sf::Vector2f pos(0.0f, 0.0f);

			sf::CircleShape hexagon(static_cast<unsigned>(BG_SIZE_OF_HEXAGON / 2), 6);
			hexagon.setFillColor(sf::Color(0, 0, 0, 0));
			hexagon.setOutlineThickness(BG_THICKNESS_OF_HEXAGON);
			hexagon.setOutlineColor(COLOR_HEXAGON);
			
			if (i % 2 == 0)
			{
				pos = sf::Vector2f((float)(j*shiftX), (float)(i*shiftY));
			}
			else
			{
				pos = sf::Vector2f((float)((j*shiftX) + (shiftX / 2)), (float)(i*shiftY));
			}

			hexagon.setPosition(pos);

			shapes.push_back(hexagon);
		}
	}
}


void BackgroundLayer::createGradientForGrid()
{
	auto windowSize = Defaults::getInstance()->getRenderWindow()->getSize();

	gradientVertices = new sf::Vertex[16]
	{
		// LEFT

		sf::Vertex(sf::Vector2f(0, 0), COLOR_GRADIENT),
		sf::Vertex(sf::Vector2f(BG_SIZE_OF_GRADIENT, 0), COLOR_TRANSPARENT),
		sf::Vertex(sf::Vector2f(BG_SIZE_OF_GRADIENT, windowSize.y), COLOR_TRANSPARENT),
		sf::Vertex(sf::Vector2f(0, windowSize.y), COLOR_GRADIENT),

		// TOP

		sf::Vertex(sf::Vector2f(0, 0), COLOR_GRADIENT),
		sf::Vertex(sf::Vector2f(0, BG_SIZE_OF_GRADIENT), COLOR_TRANSPARENT),
		sf::Vertex(sf::Vector2f(windowSize.x, BG_SIZE_OF_GRADIENT), COLOR_TRANSPARENT),
		sf::Vertex(sf::Vector2f(windowSize.x, 0), COLOR_GRADIENT),

		// RIGHT

		sf::Vertex(sf::Vector2f(windowSize.x, 0), COLOR_GRADIENT),
		sf::Vertex(sf::Vector2f(windowSize.x - BG_SIZE_OF_GRADIENT, 0), COLOR_TRANSPARENT),
		sf::Vertex(sf::Vector2f(windowSize.x - BG_SIZE_OF_GRADIENT, windowSize.y), COLOR_TRANSPARENT),
		sf::Vertex(sf::Vector2f(windowSize.x, windowSize.y), COLOR_GRADIENT),

		// BOTTOM

		sf::Vertex(sf::Vector2f(0, windowSize.y), COLOR_GRADIENT),
		sf::Vertex(sf::Vector2f(0, windowSize.y - BG_SIZE_OF_GRADIENT), COLOR_TRANSPARENT),
		sf::Vertex(sf::Vector2f(windowSize.x, windowSize.y - BG_SIZE_OF_GRADIENT), COLOR_TRANSPARENT),
		sf::Vertex(sf::Vector2f(windowSize.x, windowSize.y), COLOR_GRADIENT)
	};
}


void BackgroundLayer::onDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	for each (sf::CircleShape s in shapes)
	{
		target.draw(s);
	}


	if (gradientVertices)
	{
		target.draw(gradientVertices, 16, sf::Quads);
	}
}