#include "ArcShape.h"
#include "Maths.h"
#include "Defaults.h"

ArcShape::ArcShape(float fromAngle, float toAngle, float radius)
	: m_radius(0.0f)
	, m_thickness(0.0f)
	, m_fromAngle(0.0f)
	, m_toAngle(0.0f)
{
	m_fromAngle = fromAngle;
	m_toAngle = toAngle;
	m_radius = radius;
}

ArcShape::~ArcShape()
{
	m_vertices.clear();

	if (m_outline.size() == 0)
		return;

	for (auto it = m_outline.begin(); it != m_outline.end(); ++it)
	{
		delete (*it);
	}

	m_outline.clear();
}

bool ArcShape::contains(const sf::Vector2f& point) const
{
	std::vector<sf::Vector2f> v(m_vertices.getVertexCount());

	int range = static_cast<int>(m_vertices.getVertexCount());
	int start = 0;
	int end = range - 1;

	for (int i = 0; i < range; i++)
	{
		if (i % 2 == 0)
		{
			v[start] = sf::Vector2f(m_vertices[i].position.x, m_vertices[i].position.y);
			start++;
		}
		else
		{
			v[end] = sf::Vector2f(m_vertices[i].position.x, m_vertices[i].position.y);
			end--;
		}
	}

	return Maths::isInside(v, point);
}

void ArcShape::update()
{
	m_vertices.clear();

	float r1 = 0.0f, r2 = 0.0f;

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

	for (float k = m_fromAngle; k < m_toAngle; k++)
	{
		float x1 = (float)(cos(k * PI / 180.0f) * r1);
		float y1 = (float)(sin(k * PI / 180.0f) * r1);

		float x2 = (float)(cos(k * PI / 180.0f) * r2);
		float y2 = (float)(sin(k * PI / 180.0f) * r2);

		m_vertices.append(sf::Vector2f(x1, y1));
		m_vertices.append(sf::Vector2f(x2, y2));
	}
}

void ArcShape::setThickness(float thickness)
{
	m_thickness = thickness;
	update();
}

float ArcShape::getThickness() const
{
	return m_thickness;
}

void ArcShape::setToAngle(float toAngle)
{
	m_toAngle = toAngle;
	update();
}

float ArcShape::getToAngle() const
{
	return m_toAngle;
}

void ArcShape::setFromAngle(float fromAngle)
{
	m_fromAngle = fromAngle;
	update();
}

float ArcShape::getFromAngle() const
{
	return m_fromAngle;
}

void ArcShape::setRadius(float radius)
{
	m_radius = radius;
	update();
}

float ArcShape::getRadius() const
{
	return m_radius;
}