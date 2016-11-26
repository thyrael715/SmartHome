#pragma once

#include <SFML\Window\Event.hpp>
#include <SFML\Graphics.hpp>
#include <new>
#include <functional>

class Node;

class EventListener
{
public:

	enum class Type
	{
		UNKNOWN,
		MOUSE,
		KEYBOARD,
		VOICE
	};

	virtual ~EventListener();

	bool			isEnabled() const;
	Type			getType() const;
	std::string		getListenerID() const;
	void			onEvent(sf::Event e);
	void			setAssociatedNode(Node* node);
	Node*			getAssociatedNode() const;

protected:

	typedef			std::function<void(sf::Event e)> EventCallBack;

	Type			m_type;
	bool			m_isEnabled;
	std::string		m_listenerID;
	EventCallBack	m_onEvent;
	Node*			m_associatedNode;	
	
	EventListener();

	bool			init(Type eventType, std::string listenerID, const EventCallBack& onEvent);
};