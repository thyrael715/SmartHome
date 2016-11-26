#include "EventListener.h"


EventListener::EventListener()
	: m_isEnabled(true)
	, m_type(Type::UNKNOWN)
	, m_listenerID("__unknown_id")
	, m_onEvent(nullptr)
	, m_associatedNode(nullptr)
{

}

EventListener::~EventListener()
{

}

bool EventListener::init(Type eventType, std::string listenerID, const EventCallBack& onEvent)
{
	m_type = eventType;
	m_listenerID = listenerID;
	m_onEvent = onEvent;
	return true;
}

bool EventListener::isEnabled() const
{
	return m_isEnabled;
}

EventListener::Type EventListener::getType() const
{
	return m_type;
}

std::string EventListener::getListenerID() const
{
	return m_listenerID;
}

void EventListener::onEvent(sf::Event e)
{
	m_onEvent(e);
}

void EventListener::setAssociatedNode(Node* node)
{
	m_associatedNode = node;
}

Node* EventListener::getAssociatedNode() const
{
	return m_associatedNode;
}