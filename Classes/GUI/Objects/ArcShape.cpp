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
	size_t r1 = 0, r2 = 0;

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
		float x1 = (float)(cos(k * PI / 180.0f) * r1) + m_pos.x;
		float y1 = (float)(sin(k * PI / 180.0f) * r1) + m_pos.y;

		float x2 = (float)(cos(k * PI / 180.0f) * r2) + m_pos.x;
		float y2 = (float)(sin(k * PI / 180.0f) * r2) + m_pos.y;
		
		sf::Vertex v1(sf::Vector2f(x1, y1));
		v1.color = m_color;

		sf::Vertex v2(sf::Vector2f(x2, y2));
		v2.color = m_color;

		m_arc.push_back(v1);
		m_arc.push_back(v2);
	}
}



bool ArcShape::init()
{
	return true;
}


sf::FloatRect ArcShape::getBoundingBox() const
{
	if (m_arc.empty())
	{
		return sf::FloatRect(0, 0, 0, 0);
	}

	sf::FloatRect boundingBox(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);

	for each (const auto& item in m_arc)
	{
		if (item.position.x < boundingBox.left)
		{
			boundingBox.left = item.position.x;
		}
		if (item.position.y < boundingBox.top)
		{
			boundingBox.top = item.position.y;
		}
		if (item.position.x > boundingBox.width)
		{
			boundingBox.width = item.position.x;
		}
		if (item.position.y > boundingBox.height)
		{
			boundingBox.height = item.position.y;
		}
	}

	boundingBox.width -= boundingBox.left;
	boundingBox.height -= boundingBox.top;

	return boundingBox;
}


bool ArcShape::contains(const sf::Vector2f& point) const
{
	std::vector<sf::Vector2f> v(m_arc.size());

	int range = static_cast<int>(m_arc.size());
	int start = 0;
	int end = range - 1;

	for (int i = 0; i < range; i++)
	{
		if (i % 2 == 0)
		{
			v[start] = sf::Vector2f(m_arc[i].position.x, m_arc[i].position.y);
			start++;
		}
		else
		{
			v[end] = sf::Vector2f(m_arc[i].position.x, m_arc[i].position.y);
			end--;
		}
	}

	return Maths::isInside(v, point);
}


void ArcShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_arc.empty())
		return;

	target.draw(&m_arc[0], m_arc.size(), sf::TrianglesStrip);
}


void ArcShape::setColor(sf::Color color)
{
	for (auto& item : m_arc)
	{
		item.color = color;
	}
}

sf::Color ArcShape::getColor() const
{
	return m_color;
}

void ArcShape::setPosition(sf::Vector2f vec)
{
	for (auto& item : m_arc)
	{
		item.position = vec;
	}
}

void ArcShape::setPosition(float x, float y)
{
	for (auto& item : m_arc)
	{
		item.position.x = x;
		item.position.y = y;
	}
}

sf::Vector2f ArcShape::getPosition() const
{
	return m_pos;
}