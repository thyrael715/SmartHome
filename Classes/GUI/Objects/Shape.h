#pragma once

#include <SFML\Graphics.hpp>
#include "Object.h"

class Shape : public sf::Drawable, public Object
{
public:

	~Shape();

	void setFillColor(sf::Color color);
	sf::Color getFillColor() const;
	sf::FloatRect getGlobalBounds() const;
	sf::VertexArray getVertices() const;
	void setOutlineThickness(float thickness);
	float getOutlineThickness() const;
	void setOutlineColor(sf::Color color);
	sf::Color getOutlineColor() const;

public:

	virtual bool contains(const sf::Vector2f& point) const override = 0;
	
protected:

	Shape();

	void updateFillColor();
	void updateOutline();
	void updateOutlineColor();
	virtual void update();
	
protected:
	
	mutable sf::VertexArray m_vertices;
	std::vector<sf::Shape*> m_outline;

	float m_outlineThickness;
	sf::Color m_outlineColor;
	sf::Color m_fillColor;
	
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

}; 