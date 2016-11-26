#pragma once

#include "EventDispatcher.h"

class Node
{
public:

	Node();
	virtual ~Node();

	virtual sf::FloatRect	getBoundingBox() const = 0;
	virtual bool			contains(const sf::Vector2f& point) const = 0;

protected:
	
	virtual bool			init();

	EventDispatcher*		getEventDispatcher() const;

private:

	EventDispatcher*		m_eventDispatcher;
	sf::Vector2f			m_pos;
};