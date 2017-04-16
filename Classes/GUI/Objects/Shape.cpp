#include "Shape.h"
#include "Maths.h"

#include "Line.h"
#include "CircleShape.h"


Shape::Shape()
	: m_outlineThickness(0.0f)
	, m_outlineColor(sf::Color(255, 255, 255))
	, m_fillColor(sf::Color(255, 255, 255))
	, m_vertices(sf::TrianglesStrip)
{

}


Shape::~Shape()
{
	SAFE_DELETE_VECTOR(m_outline);
}


void Shape::onDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	if (m_outlineThickness != 0.0f && !m_outline.empty())
	{
		for (auto& item : m_outline)
		{
			target.draw(*item, states);
		}
	}

	// Draw shape and its outline
	target.draw(m_vertices, states);
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


bool Shape::contains(const sf::Vector2f& point) const
{
	bool retVal = false;

	sf::Vector2f pointInObjSpace = convertToObjectSpace(point);

	switch (m_vertices.getPrimitiveType())
	{
		case sf::TrianglesStrip:
		{
			sf::VertexArray v;
			orderVertices(m_vertices, v);
			retVal = Maths::isInside(v, pointInObjSpace);
			break;
		}
		default:
		{
			retVal = Maths::isInside(m_vertices, pointInObjSpace);
			break;
		}
	}

	return retVal;
}


void Shape::update()
{
	updateFillColor();
	updateOutline();
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
	SAFE_DELETE_VECTOR(m_outline);

	if (m_outlineThickness <= 0)
	{
		return;
	}

	// create a copy from original vertices
	sf::VertexArray tempVertices = m_vertices;

	// Circle creation lambda function of outline
	auto createCircle = [=](sf::Vector2f p) {
		CircleShape* circle = new CircleShape(m_outlineThickness, 20);
		circle->setFillColor(m_outlineColor);
		circle->setPosition(p);
		m_outline.push_back(circle);
	};

	// Line creation lambda function of outline
	auto createLine = [=](sf::Vector2f p1, sf::Vector2f p2) {
		Line* line = new Line(p1, p2, m_outlineThickness);
		line->setFillColor(m_outlineColor);
		m_outline.push_back(line);
	};

	// If the primitive type of vertexArry is sf::TriangleStrip then it has to be ordered
	// so that the outline creation will be easier.
	if (m_vertices.getPrimitiveType() == sf::TrianglesStrip)
	{
		orderVertices(m_vertices, tempVertices);
	}

	// Outline creation
	for (size_t i = 0; i < tempVertices.getVertexCount() - 1; i++)
	{
		createCircle(tempVertices[i].position);
		createLine(tempVertices[i].position, tempVertices[i + 1].position);
	}

	createCircle(tempVertices[tempVertices.getVertexCount() - 1].position);
	createLine(tempVertices[tempVertices.getVertexCount() - 1].position, tempVertices[0].position);

	// After recreation update outline color
	this->updateOutlineColor();
}


void Shape::updateOutlineColor()
{
	for (auto& item : m_outline)
	{
		item->setFillColor(m_outlineColor);
	}
}


void Shape::orderVertices(const sf::VertexArray& input, sf::VertexArray& output) const
{
	size_t range = input.getVertexCount();
	size_t start = 0;
	size_t end = range - 1;

	output.resize(range);

	for (size_t i = 0; i < range; i++)
	{
		if (i % 2 == 0)
		{
			output[start] = sf::Vector2f(input[i].position.x, input[i].position.y);
			start++;
		}
		else
		{
			output[end] = sf::Vector2f(input[i].position.x, input[i].position.y);
			end--;
		}
	}
}