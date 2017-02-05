#include "ButtonArc.h"


ButtonArc::ButtonArc(float fromAngle, float toAngle, float radius)
	: ArcShape(fromAngle, toAngle, radius)
{
	registerAllEvent();
}

ButtonArc::~ButtonArc()
{

}

void ButtonArc::onMousePressed(sf::Event e)
{
	setFillColor(sf::Color(50, 150, 75, 120));
}

void ButtonArc::onMouseReleased(sf::Event e)
{

}

void ButtonArc::onMouseMoved(sf::Event e)
{

}