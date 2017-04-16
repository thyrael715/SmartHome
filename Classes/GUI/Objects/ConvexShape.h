#pragma once


#include "Shape.h"


class ConvexShape : public Shape
{
public:

	explicit ConvexShape(std::size_t pointCount = 0);
	virtual ~ConvexShape();

	void setPointCount(std::size_t count);
	std::size_t getPointCount() const;

	void setPoint(std::size_t index, const sf::Vector2f& point);
	sf::Vector2f getPoint(std::size_t index) const;
	
protected:

	virtual void reCreate() override;

private:

	size_t m_pointCount;
};