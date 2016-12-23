#pragma once

#include <SFML\Graphics.hpp>
#include "ArcShape.h"
#include "EventDispatcher.h"
#include "Defaults.h"
#include "Object.h"

class ButtonArc : public ArcShape
{
public:
	
	ButtonArc(float fromAngle, float toAngle, float radius);
	virtual ~ButtonArc();

protected:	

	virtual bool init() override;

	void onMousePressed(sf::Event e);
	void onMouseReleased(sf::Event e);
	void onMouseScroll(sf::Event e);

private:
	
	EventListenerMouse* m_eventListener;
};