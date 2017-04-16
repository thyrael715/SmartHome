#include "CentralPanel.h"
#include "CircleShape.h"


CentralPanel::CentralPanel()
{
	
}


CentralPanel::~CentralPanel()
{
	SAFE_DELETE_VECTOR(m_mainButtons);
}


void CentralPanel::init()
{
	createInnerCircle();

	// create outer Arc 

	float radius = C2WH(300.0f);
	float thickness = C2WH(1.0f);

	auto createArc = [=](float start, float end)
	{
		ArcShape *arc = new ArcShape(start, end, radius);
		arc->setThickness(thickness);
		this->addChild(arc);
	};

	createArc(5.0f, 55.0f);
	createArc(65.0f, 85.0f);
	createArc(95.0f, 115.0f);
	createArc(125.0f, 145.0f);
	createArc(155.0f, 175.0f);
	createArc(180.0f, 300.0f);
	createArc(320.0f, 360.0f);

	createCentralCircleMenu();
}


void CentralPanel::createInnerCircle()
{
	// create rhombus wheel

	RhombusWheel* wheelShape = new RhombusWheel(C2WH(135.0f), 40, C2WW(12.0f), C2WH(7.0f));
	wheelShape->setOutlineColor(sf::Color::White);
	wheelShape->setAnimationSpeed(4.0f);
	wheelShape->startAnimation();

	this->addChild(wheelShape);

	// create blue ring

	CircleShape* circle = new CircleShape(C2WH(140.0f), 60);
	circle->setFillColor(COLOR_TRANSPARENT);
	circle->setOutlineThickness(C2WH(5.0f));
	circle->setOutlineColor(COLOR_BASECOLOR_BLUE);

	this->addChild(circle, 1);
}


void CentralPanel::createCentralCircleMenu()
{
	float radius = C2WH(200.0f);
	float thickness = C2WH(35.0f);

	for (float i = 0; i < 24; i++)
	{
		float start = (i * 15.0f) + 0.5f;
		float end = start + 14.0f;

		ButtonArc* b = new ButtonArc(start, end, radius);
		//b->setFillColor(COLOR_BASECOLOR_CIAN);
		b->setThickness(thickness);

		this->addChild(b);
	}
}