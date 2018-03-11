#include "Slider.h"
#include "MenuItem.h"


#define SLIDER_INDICATOR_FIX_SIZE	10
#define SLIDER_SIZE					10


Slider::Slider(Orientation orientation)
	: RectangleShape(ZERO)
	, m_indicator(nullptr)
	, m_objectToBeScrolled(nullptr)
	, m_orientation(orientation)
	, m_scrollableArea(ZERO)
	, m_scrollSpeed(0.0f)
{
	init();
}


Slider::~Slider()
{
	m_objectToBeScrolled = nullptr;
}


void Slider::init()
{
	m_indicator = new RectangleShape(sf::Vector2f(SLIDER_INDICATOR_FIX_SIZE, SLIDER_INDICATOR_FIX_SIZE));
	m_indicator->setFillColor(sf::Color(255, 0, 0));
	this->addChild(m_indicator);

	registerEvent(EventType::MOUSE);
}


void Slider::onMousePressed(sf::Event e)
{
	// TODO: implement it
}


void Slider::onMouseReleased(sf::Event e)
{
	// TODO: implement it
}


void Slider::onMouseMoved(sf::Event e)
{
	// TODO: implement it
}


void Slider::onMouseScrolled(sf::Event e)
{
	if (m_objectToBeScrolled &&
		m_objectToBeScrolled->getGlobalBounds().height > m_scrollableArea.y)
	{
		// align delegate object
		float newPosY = e.mouseWheelScroll.delta * m_scrollSpeed;
		float minY = -1 * (m_objectToBeScrolled->getGlobalBounds().height - m_size.y);
		float maxY = 0.0f;

		// Scrolling to the bottom of the delegate object
		if (m_objectToBeScrolled->getPosition().y + newPosY <= minY)
		{
			m_objectToBeScrolled->setPosition(sf::Vector2f(m_objectToBeScrolled->getPosition().x, minY));
		}
		// Scrolling to the top of the delegate object
		else if (m_objectToBeScrolled->getPosition().y + newPosY >= maxY)
		{
			m_objectToBeScrolled->setPosition(sf::Vector2f(m_objectToBeScrolled->getPosition().x, maxY));
		}
		// Otherwise just move the object to be scrolled
		else
		{
			m_objectToBeScrolled->move(0.0f, newPosY);
		}


		// update Indicator's position
		updateIndicatorPos();
	}
}


void Slider::updateIndicatorPos()
{
	float maxRange = m_objectToBeScrolled->getGlobalBounds().height - m_size.y;
	float currentAbsPosY = abs(m_objectToBeScrolled->getPosition().y);

	float precent = currentAbsPosY / maxRange;
	float newPosY = m_size.y * precent;
	
	if (newPosY >= m_size.y - m_indicator->getSize().y)
	{
		newPosY = m_size.y - m_indicator->getSize().y;
	}

	m_indicator->setPosition(sf::Vector2f(0.0f, newPosY));
}


void Slider::setScrollSpeed(float speed)
{
	m_scrollSpeed = speed;
}


void Slider::setObjectToBeScrolled(Object* obj)
{
	m_objectToBeScrolled = obj;
}


void Slider::setScrollableArea(const sf::Vector2f& size)
{
	m_scrollableArea = size;

	if (m_orientation == HORIZONTAL)
	{
		setSize(sf::Vector2f(m_scrollableArea.x, SLIDER_SIZE));
		setPosition(sf::Vector2f(getPosition().x, m_scrollableArea.y - SLIDER_SIZE));
	}
	else
	{
		setSize(sf::Vector2f(SLIDER_SIZE, m_scrollableArea.y));
		setPosition(sf::Vector2f(m_scrollableArea.x - SLIDER_SIZE, getPosition().y));
	}
}