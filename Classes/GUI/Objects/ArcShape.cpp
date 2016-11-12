#include "ArcShape.h"


ArcShape::ArcShape()
	: m_pos(0.0f, 0.0f)
	, m_radius(0)
	, m_thickness(0)
	, m_fromAngle(0)
	, m_toAngle(0)
	, m_color(COLOR_WHITE)
{

}

ArcShape::~ArcShape()
{
	Defaults::getInstance()->safeVectorReleaser(m_arc);
}

ArcShape* ArcShape::create(sf::Vector2f pos, size_t radius, size_t thickness, size_t fromAngle, size_t toAngle, sf::Color color)
{
	ArcShape* ret = new (std::nothrow) ArcShape();

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

void ArcShape::createWith()
{
	const size_t range = 1;
	const size_t pointCount = (2 * range) + 2;
	size_t r1, r2;

	if (m_thickness > 1)
	{
		r1 = m_radius + static_cast<size_t>(m_thickness / 2);
		r2 = m_radius - static_cast<size_t>(m_thickness / 2);
	}
	else
	{
		r1 = m_radius;
		r2 = m_radius - m_thickness;
	}

	for (size_t k = m_fromAngle; k < m_toAngle; k++)
	{
		sf::ConvexShape* tempArc = new sf::ConvexShape();

		tempArc->setPosition(m_pos);
		tempArc->setFillColor(m_color);
		tempArc->setPointCount(pointCount);

		size_t counter = 0;

		for (size_t i = 0; i <= range; i++)
		{
			float x = (float)(cos((k + i) * PI / 180.0f) * r1);
			float y = (float)(sin((k + i) * PI / 180.0f) * r1);

			tempArc->setPoint(counter, sf::Vector2f(x, y));
			counter++;
		}

		for (size_t j = 0; j <= range; j++)
		{
			float x = (float)((cos(((k + range) - j) * PI / 180.0f) * r2));
			float y = (float)((sin(((k + range) - j) * PI / 180.0f) * r2));

			tempArc->setPoint(counter, sf::Vector2f(x, y));
			counter++;
		}

		m_arc.push_back(tempArc);
	}
}

bool ArcShape::init()
{
	return true;
}


sf::FloatRect ArcShape::getBoundingBox() const
{
	sf::FloatRect boundingBox(Defaults::getInstance()->getWindowWidth(),
							  Defaults::getInstance()->getWindowHeight(),
							  0,
							  0);
	if (m_arc.empty())
	{
		return sf::FloatRect(0, 0, 0, 0);
	}

	for each (auto& shape in m_arc)
	{
		sf::FloatRect rect = shape->getGlobalBounds();

		if (boundingBox.left > rect.left)
		{
			boundingBox.left = rect.left;
		}

		if (boundingBox.top > rect.top)
		{
			boundingBox.top = rect.top;
		}

		if (boundingBox.width < rect.left + rect.width)
		{
			boundingBox.width = rect.left + rect.width;
		}

		if (boundingBox.height < rect.top + rect.height)
		{
			boundingBox.height = rect.top + rect.height;
		}
	}

	boundingBox.width -= boundingBox.left;
	boundingBox.height -= boundingBox.top;

	return boundingBox;
}


void ArcShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for each (auto& item in m_arc)
	{
		target.draw(*item);
	}
}