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

	reCreate();
}


ArcShape::~ArcShape()
{
	m_vertices.clear();
	SAFE_DELETE_VECTOR(m_outline);
}


void ArcShape::reCreate()
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

		sf::Vertex v1(sf::Vector2f(x1, y1));
		sf::Vertex v2(sf::Vector2f(x2, y2));

		m_vertices.append(v1);
		m_vertices.append(v2);
	}

	// Always needed
	this->update();
}


void ArcShape::setThickness(float thickness)
{
	m_thickness = thickness;
	reCreate();
}


float ArcShape::getThickness() const
{
	return m_thickness;
}


void ArcShape::setToAngle(float toAngle)
{
	m_toAngle = toAngle;
	reCreate();
}


float ArcShape::getToAngle() const
{
	return m_toAngle;
}


void ArcShape::setFromAngle(float fromAngle)
{
	m_fromAngle = fromAngle;
	reCreate();
}


float ArcShape::getFromAngle() const
{
	return m_fromAngle;
}


void ArcShape::setRadius(float radius)
{
	m_radius = radius;
	reCreate();
}


float ArcShape::getRadius() const
{
	return m_radius;
}