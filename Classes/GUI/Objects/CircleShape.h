#pragma once

#include <SFML\Graphics.hpp>
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

public:

	virtual bool contains(const sf::Vector2f& point) const override;

protected:

	virtual void create() override;

private:

	float m_radius;
	size_t m_pointCount;
};