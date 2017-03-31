
#include "ConvexShape.h"



ConvexShape::ConvexShape(size_t pointCount)
	: m_pointCount(pointCount)
{
	m_vertices.setPrimitiveType(sf::TrianglesFan);
	create();
}


ConvexShape::~ConvexShape()
{

}


void ConvexShape::create()
{
	m_vertices.clear();

	for (size_t i = 0; i < m_pointCount; i++)
	{
		m_vertices.append(sf::Vector2f(0.0f, 0.0f));
	}
}


void ConvexShape::setPointCount(size_t count)
{
	m_pointCount = count;
	create();
}


size_t ConvexShape::getPointCount() const
{
	return m_pointCount;
}


void ConvexShape::setPoint(size_t index, const sf::Vector2f& point)
{
	if (index >= m_vertices.getVertexCount())
		return;

	m_vertices[index].position = point;
}


sf::Vector2f ConvexShape::getPoint(size_t index) const
{
	if (index >= m_vertices.getVertexCount())
		return sf::Vector2f(0.0f, 0.0f);

	return m_vertices[index].position;
}


bool ConvexShape::contains(const sf::Vector2f& point) const
{
	return true;
}