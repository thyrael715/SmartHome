#include "Node.h"

Node::Node()
	: m_eventDispatcher(nullptr)
{
	init();
}

Node::~Node()
{

}

bool Node::init()
{
	m_eventDispatcher = EventDispatcher::getInstance();
	return true;
}

EventDispatcher* Node::getEventDispatcher() const
{
	return m_eventDispatcher;
}