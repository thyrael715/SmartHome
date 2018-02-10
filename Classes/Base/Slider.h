#pragma once

#include "RectangleShape.h"

class Slider : public RectangleShape
{
public:

	Slider(Orientation orientation);
	virtual ~Slider();

	void init();
	void setObjectToBeScrolled(Object* obj);
	void setScrollableArea(const sf::Vector2f& size);

public:
	
	virtual void onMousePressed(sf::Event e) override;
	virtual void onMouseReleased(sf::Event e) override;
	virtual void onMouseMoved(sf::Event e) override;
	virtual void onMouseScrolled(sf::Event e) override;

private:

	void updateIndicatorPos();

	RectangleShape* m_indicator;
	Object* m_objectToBeScrolled;
	Orientation m_orientation;
	sf::Vector2f m_scrollableArea;

	float m_delta;
};