#pragma once

#include <SFML\Graphics.hpp>
#include "Shape.h"


class ArcShape : public Shape
{
public:

	ArcShape(float fromAngle, float toAngle, float radius);
	virtual ~ArcShape();

	void	setThickness(float thickness);
	float	getThickness() const;

	void	setToAngle(float toAngle);
	float	getToAngle() const;

	void	setFromAngle(float fromAngle);
	float	getFromAngle() const;

	void	setRadius(float radius);
	float	getRadius() const;

public:

	virtual bool contains(const sf::Vector2f& point) const override;

protected:

	virtual void update() override;

protected:
	
	float m_radius;
	float m_thickness;
	float m_fromAngle;
	float m_toAngle;
};	