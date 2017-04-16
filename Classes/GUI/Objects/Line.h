#pragma once


#include "Shape.h"

class Line : public Shape
{
public:

	Line(sf::Vector2f start, sf::Vector2f end, float thickness);
	virtual ~Line();

	void setThickness(float thickness);
	float getThickness() const;

protected:

	virtual void reCreate() override;

protected:

	float m_thickness;

	sf::Vector2f m_p1;
	sf::Vector2f m_p2;
};