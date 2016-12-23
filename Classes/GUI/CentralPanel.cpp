#include "CentralPanel.h"
#include "Defaults.h"


CentralPanel::CentralPanel()
{

}

CentralPanel::~CentralPanel()
{
	delete m_wheelShape;

	Defaults::getInstance()->safeVectorReleaser(m_outerArc);
	Defaults::getInstance()->safeVectorReleaser(m_mainButtons);
}

CentralPanel* CentralPanel::create()
{
	CentralPanel* cp = new CentralPanel();
	cp->init();

	return cp;
}

void CentralPanel::init()
{
	sf::Vector2f windowCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	// create rhombus wheel

	m_wheelShape = RhombusWheel::create(windowCenter, C2WH(150.0f), 40, C2WW(12.0f), C2WH(7.0f));
	m_wheelShape->setAnimCenter(windowCenter);
	m_wheelShape->setAnimAngle(0.0025f);
	m_wheelShape->startAnimation();

	// create outer Arc 

	float radius = C2WH(250.0f);
	float thickness = C2WH(1.0f);
	
	for (size_t i = 0; i < 7; i++)
	{
		ArcShape *arc = new ArcShape(35 + (i * 30), 55 + (i * 30), radius);
		arc->setThickness(thickness);
		arc->setPosition(windowCenter);
		m_outerArc.push_back(arc);
	}

	createCentralCircleMenu();
}


void CentralPanel::createCentralCircleMenu()
{
	sf::Vector2f windowCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	float radius = C2WH(200.0f);
	float thickness = C2WH(35.0f);

	for (float i = 0; i < 24; i++)
	{
		float start = (i * 15.0f) + 0.5f;
		float end = start + 14.0f;

		ButtonArc* b = new ButtonArc(start, end, radius);
		b->setFillColor(sf::Color(25, 75, 125));
		b->setThickness(thickness);
		b->setPosition(windowCenter);

		m_mainButtons.push_back(b);
	}
}


void CentralPanel::draw(sf::RenderWindow& window) const
{
	m_wheelShape->draw(window);

	for each (auto& item in m_outerArc)
	{
		window.draw(*item);
	}

	for each (auto& item in m_mainButtons)
	{
		window.draw(*item);
	}
}