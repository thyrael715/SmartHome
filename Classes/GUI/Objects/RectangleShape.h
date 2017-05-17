#pragma once

#include "Shape.h"


class RectangleShape : public Shape
{
public:

	explicit RectangleShape(const sf::Vector2f& size = sf::Vector2f(0, 0));
	virtual ~RectangleShape();

	void setSize(const sf::Vector2f& size);
	sf::Vector2f getSize() const;

protected:

	virtual void reCreate() override;

private:

	sf::Vector2f m_size;
};