#pragma once


#include "Object.h"


class Shape : public Object
{
public:

	virtual ~Shape();

	void setFillColor(sf::Color color);
	sf::Color getFillColor() const;
	sf::FloatRect getGlobalBounds() const;
	sf::VertexArray getVertices() const;
	void setOutlineThickness(float thickness);
	float getOutlineThickness() const;
	void setOutlineColor(sf::Color color);
	sf::Color getOutlineColor() const;

public:

	virtual bool contains(const sf::Vector2f& point) const;
	
protected:

	Shape();

	virtual void reCreate() = 0;

	void update();

	void updateFillColor();
	void updateOutline();
	void updateOutlineColor();

	void orderVertices(const sf::VertexArray& input, sf::VertexArray& output) const;
	
protected:
	
	mutable sf::VertexArray m_vertices;
	std::vector<Shape*> m_outline;

	float m_outlineThickness;
	sf::Color m_outlineColor;
	sf::Color m_fillColor;
	
private:

	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates& states) const override;

}; 