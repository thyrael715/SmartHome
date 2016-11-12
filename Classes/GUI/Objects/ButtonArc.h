#pragma once

#include <SFML\Graphics.hpp>
#include "Defaults.h"
#include "ArcShape.h"


class ButtonArc : public ArcShape
{
public:

	virtual ~ButtonArc();

	static ButtonArc* create(sf::Vector2f pos, size_t radius, size_t thickness, size_t fromAngle, size_t toAngle, sf::Color color = COLOR_WHITE);

protected:

	virtual bool init() override;

	void onMousePressed(sf::Event e);
	void onMouseReleased(sf::Event e);
	void onMouseScroll(sf::Event e);

private:
	
	EventListenerMouse* m_eventListener;

	explicit ButtonArc();
};