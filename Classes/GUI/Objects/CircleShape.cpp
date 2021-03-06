
#include "CircleShape.h"
#include "Defaults.h"


CircleShape::CircleShape(float radius, size_t pointCount)
	: m_radius(radius)
	, m_pointCount(pointCount)
{
	m_vertices.setPrimitiveType(sf::TrianglesFan);
	reCreate();
}


CircleShape::~CircleShape()
{

}


void CircleShape::reCreate()
{
	m_vertices.clear();

	float angle = 360.0f / m_pointCount;

	for (size_t i = 0; i < m_pointCount; i++)
	{	
		float x1 = (float)(cos((i*angle) * PI / 180.0f) * m_radius);
		float y1 = (float)(sin((i*angle) * PI / 180.0f) * m_radius);

		m_vertices.append(sf::Vector2f(x1, y1));
	}

	// Always needed
	this->update();
}


void CircleShape::setRadius(float radius)
{
	m_radius = radius;
	reCreate();
}


float CircleShape::getRadius() const
{
	return m_radius;
}


void CircleShape::setPointCount(size_t count)
{
	m_pointCount = count;
	reCreate();
}


std::size_t CircleShape::getPointCount() const
{
	return m_pointCount;
}