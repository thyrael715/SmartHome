#pragma once

#include "EventDispatcher.h"

class Node
{
public:

	Node();
	virtual ~Node();

protected:
	
	virtual bool init();
	virtual sf::FloatRect getBoundingBox() const = 0;

	EventDispatcher* getEventDispatcher() const;

private:

	EventDispatcher* m_eventDispatcher;
};