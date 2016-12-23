#include "Object.h"

Object::Object()
	: m_eventDispatcher(nullptr)
{
	init();
}

Object::~Object()
{
	
}

bool Object::init()
{
	m_eventDispatcher = EventDispatcher::getInstance();
	return true;
}

EventDispatcher* Object::getEventDispatcher() const
{
	return m_eventDispatcher;
}
