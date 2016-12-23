#pragma once

#include "EventDispatcher.h"
#include "Defaults.h"
#include <list>

class Object : public sf::Transformable
{
public:

	Object();
	virtual ~Object();
	virtual bool contains(const sf::Vector2f& point) const = 0;

protected:
	
	virtual bool init();

protected:

	EventDispatcher* getEventDispatcher() const;

private:

	EventDispatcher* m_eventDispatcher;
};