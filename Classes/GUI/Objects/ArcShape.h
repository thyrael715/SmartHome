#pragma once

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
	
protected:

	virtual void reCreate() override;

protected:
	
	float m_radius;
	float m_thickness;
	float m_fromAngle;
	float m_toAngle;
};	