
#include "ConvexShape.h"



ConvexShape::ConvexShape(size_t pointCount)
	: m_pointCount(pointCount)
{
	m_vertices.setPrimitiveType(sf::TrianglesFan);
	reCreate();
}


ConvexShape::~ConvexShape()
{

}


void ConvexShape::reCreate()
{
	m_vertices.clear();

	for (size_t i = 0; i < m_pointCount; i++)
	{
		m_vertices.append(sf::Vector2f(0.0f, 0.0f));
	}

	// Always needed
	this->update();
}


void ConvexShape::setPointCount(size_t count)
{
	m_pointCount = count;
	reCreate();
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