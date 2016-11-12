#include "ButtonArc.h"


ButtonArc::ButtonArc()
	: m_eventListener(nullptr)
{

}

ButtonArc::~ButtonArc()
{

}

ButtonArc* ButtonArc::create(sf::Vector2f pos, size_t radius, size_t thickness, size_t fromAngle, size_t toAngle, sf::Color color)
{
	ButtonArc* ret = new ButtonArc();

	if (ret && ret->init())
	{
		ret->m_pos = pos;
		ret->m_radius = radius;
		ret->m_thickness = thickness;
		ret->m_fromAngle = fromAngle;
		ret->m_toAngle = toAngle;
		ret->m_color = color;

		ret->createWith();

		return ret;
	}

	return nullptr;
}

bool ButtonArc::init()
{
	m_eventListener = EventListenerMouse::create();

	if (m_eventListener == nullptr)
		return false;
	
	m_eventListener->onMousePressed = CALLBACK_1(ButtonArc::onMousePressed, this);
	m_eventListener->onMouseReleased = CALLBACK_1(ButtonArc::onMouseReleased, this);

	getEventDispatcher()->addEventListener(m_eventListener, this);

	return true;
}

void ButtonArc::onMousePressed(sf::Event e)
{
	sf::FloatRect boundingBox = getBoundingBox();

	if (e.mouseButton.x > boundingBox.left &&
		e.mouseButton.x < boundingBox.left + boundingBox.width &&
		e.mouseButton.y > boundingBox.top &&
		e.mouseButton.y < boundingBox.top + boundingBox.height)
	{
		std::cout << "\n\rButton <" << "> has been pressed!";
	}
}

void ButtonArc::onMouseReleased(sf::Event e)
{

}

void ButtonArc::onMouseScroll(sf::Event e)
{

}