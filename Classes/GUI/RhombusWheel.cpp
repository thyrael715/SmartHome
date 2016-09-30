#include "RhombusWheel.h"


RhombusWheel::RhombusWheel()
	: m_pos(0.0f, 0.0f)
	, m_color(sf::Color(255, 255, 255))
	, m_radius(0.0f)
	, m_width(0.0f)
	, m_height(0.0f)
	, m_wheelPartCount(0)
	, m_animAngle(0.0f)
	, m_animCenter(0.0f, 0.0f)
	, m_isAnimating(false)
{

}

RhombusWheel::~RhombusWheel()
{
	m_wheelShape.clear();
}

RhombusWheel* RhombusWheel::create(sf::Vector2f pos, float radius, size_t count, float w, float h, sf::Color color)
{
	RhombusWheel* wheel = new RhombusWheel();
	wheel->m_pos = pos;
	wheel->m_radius = radius;
	wheel->m_wheelPartCount = count;
	wheel->m_width = w;
	wheel->m_height = h;
	wheel->m_color = color;

	wheel->createWheel();

	return wheel;
}


void RhombusWheel::createWheel()
{
	float angle = 360.0f / m_wheelPartCount;

	for (size_t i = 0; i < m_wheelPartCount; i++)
	{
		sf::ConvexShape cs;

		float x = (float)(cos(i * angle * PI / 180.0f) * m_radius) + m_pos.x;
		float y = (float)(sin(i * angle * PI / 180.0f) * m_radius) + m_pos.y;

		cs.setPointCount(4);

		// define the points
		cs.setPoint(0, sf::Vector2f(0, 0));
		cs.setPoint(1, sf::Vector2f(0, m_width));
		cs.setPoint(2, sf::Vector2f(m_height, m_width + m_height));
		cs.setPoint(3, sf::Vector2f(m_height, m_height));
		cs.setOrigin(m_height / 2, (m_width + m_height) / 2);
		cs.setPosition(x, y);
		cs.rotate(i*angle);
		cs.setFillColor(m_color);

		m_wheelShape.push_back(cs);
	}
}


void RhombusWheel::reCreate()
{
	m_wheelShape.clear();
	createWheel();
}


void RhombusWheel::draw(sf::RenderWindow& window)
{
	for each (auto& item in m_wheelShape)
	{
		if (m_isAnimating)
		{
			m_transform.rotate(m_animAngle, { m_animCenter.x, m_animCenter.y });
		}

		window.draw(item, m_transform);
	}
}


void RhombusWheel::setColor(sf::Color color)
{
	m_color = color;
	
	for each (auto shape in m_wheelShape)
	{
		shape.setFillColor(color);
	}
}

sf::Color RhombusWheel::getColor() const
{
	return m_color;
}

void RhombusWheel::setPosition(sf::Vector2f pos)
{
	m_pos = pos;

	for each (auto shape in m_wheelShape)
	{
		shape.setPosition(pos);
	}
}

void RhombusWheel::setPositionX(float posX)
{
	m_pos.x = posX;

	for each (auto shape in m_wheelShape)
	{
		float y = shape.getPosition().y;
		shape.setPosition(posX, y);
	}
}

void RhombusWheel::setPositionY(float posY)
{
	m_pos.y = posY;

	for each (auto shape in m_wheelShape)
	{
		float x = shape.getPosition().x;
		shape.setPosition(x, posY);
	}
}

sf::Vector2f RhombusWheel::getPosition() const
{
	return m_pos;
}

void RhombusWheel::setAnimAngle(float angle)
{
	m_animAngle = angle;
}

void RhombusWheel::setAnimCenter(sf::Vector2f center)
{
	m_animCenter = center;
}

void RhombusWheel::startAnimation()
{
	m_isAnimating = true;
}

void RhombusWheel::stopAnimation()
{
	m_isAnimating = false;
}