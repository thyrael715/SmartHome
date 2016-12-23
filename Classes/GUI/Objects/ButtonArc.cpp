#include "ButtonArc.h"


ButtonArc::ButtonArc(float fromAngle, float toAngle, float radius)
	: ArcShape(fromAngle, toAngle, radius)
	, m_eventListener(nullptr)
{

}

ButtonArc::~ButtonArc()
{
	EventDispatcher::getInstance()->removeEventListener(m_eventListener);
	SAFE_DELETE(m_eventListener);
}

bool ButtonArc::init()
{
	m_eventListener = EventListenerMouse::create();

	if (m_eventListener == nullptr)
		return false;

	m_eventListener->onMousePressed = CALLBACK_1(ButtonArc::onMousePressed, this);
	m_eventListener->onMouseReleased = CALLBACK_1(ButtonArc::onMouseReleased, this);

	EventDispatcher::getInstance()->addEventListener(m_eventListener, this);

	return true;
}

void ButtonArc::onMousePressed(sf::Event e)
{
	setFillColor(sf::Color(50, 150, 75, 120));
}

void ButtonArc::onMouseReleased(sf::Event e)
{

}

void ButtonArc::onMouseScroll(sf::Event e)
{

}