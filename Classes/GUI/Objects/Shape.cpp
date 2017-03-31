#include "Shape.h"
#include "Maths.h"

Shape::Shape()
	: m_outlineThickness(0.0f)
	, m_outlineColor(sf::Color(255, 255, 255))
	, m_fillColor(sf::Color(255, 255, 255))
	, m_vertices(sf::TrianglesStrip)
{

}

Shape::~Shape()
{
	sf::VertexArray m_vertices;
	std::vector<sf::Shape*> m_outline;
}

void Shape::onDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	// Draw shape and its outline
	target.draw(m_vertices, states);

	if (m_outlineThickness != 0.0f && !m_outline.empty())
	{
		for (auto& item : m_outline)
		{
			target.draw(*item, states);
		}
	}
}

void Shape::setFillColor(sf::Color color)
{
	m_fillColor = color;
	updateFillColor();
}

sf::Color Shape::getFillColor() const
{
	return m_outlineColor;
}

sf::FloatRect Shape::getGlobalBounds() const
{
	return m_vertices.getBounds();
}

sf::VertexArray Shape::getVertices() const
{
	return m_vertices;
}

void Shape::setOutlineThickness(float thickness)
{
	m_outlineThickness = thickness;
	updateOutline();
}

float Shape::getOutlineThickness() const
{
	return m_outlineThickness;
}

void Shape::setOutlineColor(sf::Color color)
{
	m_outlineColor = color;
	updateOutlineColor();
}

sf::Color Shape::getOutlineColor() const
{
	return m_outlineColor;
}

void Shape::updateFillColor()
{
	for (size_t i = 0; i < m_vertices.getVertexCount(); i++)
	{
		m_vertices[i].color = m_fillColor;
	}
}

void Shape::updateOutline()
{
	/*if (!m_outline.empty())
		Defaults::getInstance()->safeVectorReleaser(m_outline);

	for (size_t i = 0; i < m_arc.size() - 1; i++)
	{
		sf::CircleShape circle;
		circle.setFillColor(color);
		circle.setPosition(m_arc[i].position);
		circle.setRadius(thickness / 2.0f);

		sf::RectangleShape rect(m_arc[i].position - sf::Vector2f(0.0f, thickness / 2.0f));
		rect.setFillColor(color);
		rect.setPosition();
		rect.s
	}*/
}

void Shape::updateOutlineColor()
{
	for (auto& item : m_outline)
	{
		item->setFillColor(m_outlineColor);
	}
}
