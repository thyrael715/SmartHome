
#include "RhombusWheel.h"
#include "ConvexShape.h"
#include "Defaults.h"


RhombusWheel::RhombusWheel(float radius, size_t count, float rhombus_w, float rhombus_h)
	: m_outlineColor(COLOR_WHITE)
	, m_radius(radius)
	, m_rhombusWidth(rhombus_w)
	, m_rhombusHeight(rhombus_h)
	, m_wheelPartCount(count)
	, m_animationSpeed(0.0f)
	, m_isAnimating(false)
{
	reCreate();
	Scheduler::getInstance()->scheduleUpdate(this);
}


RhombusWheel::~RhombusWheel()
{

}


void RhombusWheel::reCreate()
{
	this->removeAllChildren();

	const float angle = 360.0f / m_wheelPartCount;

	for (size_t i = 0; i < m_wheelPartCount; i++)
	{
		ConvexShape* cs = new ConvexShape(4);

		const float x = (float)(cos(i * angle * PI / 180.0f) * m_radius);
		const float y = (float)(sin(i * angle * PI / 180.0f) * m_radius);

		// define the points
		cs->setPoint(0, sf::Vector2f(0, 0));
		cs->setPoint(1, sf::Vector2f(0, m_rhombusWidth));
		cs->setPoint(2, sf::Vector2f(m_rhombusHeight, m_rhombusWidth + m_rhombusHeight));
		cs->setPoint(3, sf::Vector2f(m_rhombusHeight, m_rhombusHeight));

		cs->setOrigin(m_rhombusHeight / 2, (m_rhombusWidth + m_rhombusHeight) / 2);
		cs->setPosition(x, y);
		cs->rotate(i*angle);
		cs->setFillColor(m_outlineColor);

		this->addChild(cs);
	}
}


void RhombusWheel::onUpdate(float dt)
{
	if (m_isAnimating)
	{
		setRotation(getRotation() + (m_animationSpeed * dt));
	}
}


void RhombusWheel::setOutlineColor(sf::Color color)
{
	m_outlineColor = color;
	
	for (auto& actChild : getChildren())
	{
		if (auto child = dynamic_cast<Shape*>(actChild))
		{
			child->setFillColor(color);
		}
	}
}

sf::Color RhombusWheel::getOutlineColor() const
{
	return m_outlineColor;
}


void RhombusWheel::setRadius(float radius)
{
	m_radius = radius;
	reCreate();
}


float RhombusWheel::getRadius() const
{
	return m_radius;
}


void RhombusWheel::setWheelPartCount(size_t wheelPartCount)
{
	m_wheelPartCount = wheelPartCount;
	reCreate();
}


size_t RhombusWheel::getWheelPartCount() const
{
	return m_wheelPartCount;
}


void RhombusWheel::setAnimationSpeed(float angle)
{
	m_animationSpeed = angle;
}


void RhombusWheel::startAnimation()
{
	m_isAnimating = true;
}


void RhombusWheel::stopAnimation()
{
	m_isAnimating = false;
}

