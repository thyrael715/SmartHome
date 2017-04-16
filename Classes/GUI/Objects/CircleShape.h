#pragma once


#include "Shape.h"


class CircleShape : public Shape
{
public:

	explicit CircleShape(float radius = 0, size_t pointCount = 30);
	virtual ~CircleShape();

	void setRadius(float radius);
	float getRadius() const;
	void setPointCount(size_t count);
	std::size_t getPointCount() const;

protected:

	virtual void reCreate() override;

private:

	float m_radius;
	size_t m_pointCount;
};