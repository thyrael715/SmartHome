#include "RectangleShape.h"


RectangleShape::RectangleShape(const sf::Vector2f& size)
	: m_size(size)
{
	m_vertices.setPrimitiveType(sf::TrianglesFan);
	reCreate();
}


RectangleShape::~RectangleShape()
{

}


void RectangleShape::setSize(const sf::Vector2f& size)
{
	m_size = size;
	reCreate();
}


sf::Vector2f RectangleShape::getSize() const
{
	return m_size;
}


void RectangleShape::reCreate()
{
	m_vertices.clear();

	m_vertices.append(sf::Vector2f(0, 0));
	m_vertices.append(sf::Vector2f(m_size.x, 0));
	m_vertices.append(sf::Vector2f(m_size.x, m_size.y));
	m_vertices.append(sf::Vector2f(0, m_size.y));

	// Always needed
	this->update();
}