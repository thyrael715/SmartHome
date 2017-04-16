#include "Line.h"


Line::Line(sf::Vector2f start, sf::Vector2f end, float thickness)
	: m_thickness(thickness)
	, m_p1(start)
	, m_p2(end)
{
	reCreate();
}

Line::~Line()
{

}

void Line::reCreate()
{
	m_vertices.clear();

	float d = std::sqrt(std::pow(m_p2.x - m_p1.x, 2.0f) + std::pow(m_p2.y - m_p1.y, 2.0f));
	float scaleFactor = m_thickness / d;

	sf::Vector2f gradient = m_p1 - m_p2;
	sf::Vector2f n(gradient.y, -gradient.x);

	m_vertices.append(m_p1 + sf::Vector2f(n * scaleFactor));
	m_vertices.append(m_p2 + sf::Vector2f(n * scaleFactor));
	m_vertices.append(m_p1 + sf::Vector2f((-1.0f * n) * scaleFactor));
	m_vertices.append(m_p2 + sf::Vector2f((-1.0f * n) * scaleFactor));

	// Always needed
	this->update();
}


void Line::setThickness(float thickness)
{
	m_thickness = thickness;
	reCreate();
}


float Line::getThickness() const
{
	return m_thickness;
}