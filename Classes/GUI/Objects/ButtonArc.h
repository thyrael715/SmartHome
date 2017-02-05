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

	virtual void onMousePressed(sf::Event e) override;
	virtual void onMouseReleased(sf::Event e) override;
	virtual void onMouseMoved(sf::Event e) override;

private:
};