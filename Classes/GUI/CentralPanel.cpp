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

	size_t radius = C2WH(250);
	size_t thickness = C2WH(1);

	m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 5, 55));
	m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 65, 85));
	m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 95, 115));
	m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 125, 145));
	m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 155, 175));
	m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 180, 300));
	m_outerArc.push_back(ArcShape::create(windowCenter, radius, thickness, 320, 360));

	createCentralCircleMenu();
}


void CentralPanel::createCentralCircleMenu()
{
	sf::Vector2f windowCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	size_t radius = C2WH(200);
	size_t thickness = C2WH(35);

	m_mainButtons.push_back(ButtonArc::create(windowCenter, radius, thickness, 305, 320));
	m_mainButtons.push_back(ButtonArc::create(windowCenter, radius, thickness, 325, 340));
	m_mainButtons.push_back(ButtonArc::create(windowCenter, radius, thickness, 345, 360));
	m_mainButtons.push_back(ButtonArc::create(windowCenter, radius, thickness, 5, 20));
	m_mainButtons.push_back(ButtonArc::create(windowCenter, radius, thickness, 25, 40));

	m_mainButtons.push_back(ButtonArc::create(windowCenter, radius, thickness, 140, 155));
	m_mainButtons.push_back(ButtonArc::create(windowCenter, radius, thickness, 160, 175));
	m_mainButtons.push_back(ButtonArc::create(windowCenter, radius, thickness, 180, 195));
	m_mainButtons.push_back(ButtonArc::create(windowCenter, radius, thickness, 200, 215));
	m_mainButtons.push_back(ButtonArc::create(windowCenter, radius, thickness, 220, 235));
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