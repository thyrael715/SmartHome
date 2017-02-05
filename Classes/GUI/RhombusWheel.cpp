#include "RhombusWheel.h"


RhombusWheel::RhombusWheel(float radius, size_t count, float w, float h)
	: m_outlineColor(COLOR_WHITE)
	, m_radius(0.0f)
	, m_width(0.0f)
	, m_height(0.0f)
	, m_wheelPartCount(0)
	, m_animAngle(0.0f)
	, m_animCenter(0.0f, 0.0f)
	, m_isAnimating(false)
{
	m_radius = radius;
	m_wheelPartCount = count;
	m_width = w;
	m_height = h;

	create();
}

RhombusWheel::~RhombusWheel()
{
	SAVE_DELETE_VECTOR(m_wheelShape);
}

void RhombusWheel::create()
{
	const float angle = 360.0f / m_wheelPartCount;

	for (size_t i = 0; i < m_wheelPartCount; i++)
	{
		sf::ConvexShape* cs = new sf::ConvexShape();

		const float x = (float)(cos(i * angle * PI / 180.0f) * m_radius);
		const float y = (float)(sin(i * angle * PI / 180.0f) * m_radius);

		cs->setPointCount(4);
		
		// define the points
		cs->setPoint(0, sf::Vector2f(0, 0));
		cs->setPoint(1, sf::Vector2f(0, m_width));
		cs->setPoint(2, sf::Vector2f(m_height, m_width + m_height));
		cs->setPoint(3, sf::Vector2f(m_height, m_height));
		cs->setOrigin(m_height / 2, (m_width + m_height) / 2);
		cs->setPosition(x, y);
		cs->rotate(i*angle);
		cs->setFillColor(m_outlineColor);

		m_wheelShape.push_back(cs);
	}
}

void RhombusWheel::reCreate()
{
	SAVE_DELETE_VECTOR(m_wheelShape);
	create();
}

sf::FloatRect RhombusWheel::getGlobalBounds() const
{
	if (m_wheelShape.empty())
	{
		return sf::FloatRect(0, 0, 0, 0);
	}

	sf::FloatRect boundingBox(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);

	for each (const auto& item in m_wheelShape)
	{
		if (item->getPosition().x < boundingBox.left)
		{
			boundingBox.left = item->getPosition().x;
		}
		if (item->getPosition().y < boundingBox.top)
		{
			boundingBox.top = item->getPosition().y;
		}
		if (item->getPosition().x > boundingBox.width)
		{
			boundingBox.width = item->getPosition().x;
		}
		if (item->getPosition().y > boundingBox.height)
		{
			boundingBox.height = item->getPosition().y;
		}
	}

	boundingBox.width -= boundingBox.left;
	boundingBox.height -= boundingBox.top;

	return boundingBox;
}

bool RhombusWheel::contains(const sf::Vector2f& point) const
{
	return false;
}

void RhombusWheel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	static sf::Transform transform;

	// Combine transforms
	states.transform *= getTransform();

	for each (auto& item in m_wheelShape)
	{
		if (m_isAnimating)
		{
			transform.rotate(m_animAngle, { m_animCenter.x, m_animCenter.y });
		}

		target.draw(*item, transform);
	}
}


void RhombusWheel::setOutlineColor(sf::Color color)
{
	m_outlineColor = color;
	
	for (sf::ConvexShape*& item : m_wheelShape)
	{
		item->setFillColor(color);
	}
}

sf::Color RhombusWheel::getOutlineColor() const
{
	return m_outlineColor;
}

//void RhombusWheel::setPosition(sf::Vector2f pos)
//{
//	Object::setPosition(pos);
//
//	for (size_t item = 0; item < m_wheelShape.size(); item++)
//	{
//		static_cast<sf::ConvexShape>(item).setPosition(pos);
//	}
//}
//
//void RhombusWheel::setPosition(float posX, float posY)
//{
//	Object::setPosition(posX, posY);
//
//	for (size_t item = 0; item < m_wheelShape.size(); item++)
//	{
//		sf::ConvexShape convexShape = static_cast<sf::ConvexShape>(item);
//
//		float y = convexShape.getPosition().y;
//		convexShape.setPosition(posX, posY);
//	}
//}

void RhombusWheel::setRadius(float radius)
{
	m_radius = radius;
	reCreate();
}

float RhombusWheel::getRadius() const
{
	return m_radius;
}

void RhombusWheel::setWidth(float width)
{
	m_width = width;
	reCreate();
}

float RhombusWheel::getWidth() const
{
	return m_width;
}

void RhombusWheel::setHeight(float height)
{
	m_height = height;
	reCreate();
}

float RhombusWheel::getHeight() const
{
	return m_height;
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

