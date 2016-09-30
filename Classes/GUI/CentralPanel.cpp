#include "CentralPanel.h"
#include "Defaults.h"
#include <iostream>


CentralPanel::CentralPanel()
{
	init();
}

CentralPanel::~CentralPanel()
{
	delete m_wheelShape;
}

CentralPanel* CentralPanel::create()
{
	static CentralPanel* cp = new CentralPanel();
	return cp;
}

void CentralPanel::init()
{
	// create rhombus wheel

	const float animSpeed = 0.0025f;
	const float radius = 200.0f;
	const unsigned int count = 40;
	const float rWidth = 12.0f;
	const float rHeight = 7.0f;

	sf::Vector2f windowCenter(Defaults::getInstance()->getWindowWidth() / 2,
							  Defaults::getInstance()->getWindowHeight() / 2);

	m_wheelShape = RhombusWheel::create(windowCenter, radius, count, rWidth, rHeight);
	m_wheelShape->setAnimCenter(windowCenter);
	m_wheelShape->setAnimAngle(animSpeed);
	m_wheelShape->startAnimation();

	createWheel();
}

void CentralPanel::createWheel()
{
	int r1 = 100;
	int r2 = 80;
	int angle2 = 270;
	int startAngle = 0;

	for (int k = startAngle; k < 360; k++)
	{
		sf::ConvexShape tempArc;
		sf::Color color;
		
		if (k > 270)
		{
			color = sf::Color(0, 110, 175);
		}
		else
		{
			color = sf::Color(0, 220, 255);
		}

		tempArc.setFillColor(color);
		tempArc.setPosition(640, 360);
		tempArc.setPointCount(6);
		int counter = 0;

		for (int i = k; i <= k + 2; i++)
		{
			float x = (float)(cos(i * PI / 180.0) * r1);
			float y = (float)(sin(i * PI / 180.0) * r1);

			tempArc.setPoint(counter, sf::Vector2f(x, y));
			counter++;
		}

		for (int j = k + 2; j >= k; --j)
		{
			float x = (float)(cos(j * PI / 180.0) * r2);
			float y = (float)(sin(j * PI / 180.0) * r2);

			tempArc.setPoint(counter, sf::Vector2f(x, y));
			counter++;
		}

		m_arc.push_back(tempArc);
	}
}

void CentralPanel::draw(sf::RenderWindow& window) const
{
	m_wheelShape->draw(window);

	for each (auto& actArc in m_arc)
	{
		window.draw(actArc);
	}	
}