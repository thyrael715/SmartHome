#include "CentralPanel.h"
#include "Defaults.h"


CentralPanel::CentralPanel()
{

}

CentralPanel::~CentralPanel()
{
	SAFE_DELETE(m_wheelShape);

	SAVE_DELETE_VECTOR(m_outerArc);
	SAVE_DELETE_VECTOR(m_mainButtons);
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

	m_wheelShape = new RhombusWheel(C2WH(150.0f), 40, C2WW(12.0f), C2WH(7.0f));
	m_wheelShape->setPosition(windowCenter);
	//m_wheelShape->setAnimCenter(windowCenter);
	//m_wheelShape->setAnimAngle(0.0025f);
	//m_wheelShape->startAnimation();

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

	//m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 5, 55));
	//m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 65, 85));
	//m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 95, 115));
	//m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 125, 145));
	//m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 155, 175));
	//m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 180, 300));
	//m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 320, 360));


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
	window.draw(*m_wheelShape);

	for each (auto& item in m_outerArc)
	{
		window.draw(*item);
	}

	for each (auto& item in m_mainButtons)
	{
		window.draw(*item);
	}
}