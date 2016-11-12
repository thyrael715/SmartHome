#pragma once

#include <SFML\Window\Event.hpp>
#include <SFML\Graphics.hpp>
#include <new>
#include <functional>


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

protected:

	typedef			std::function<void(sf::Event e)> EventCallBack;

	std::string		m_listenerID;
	EventCallBack	m_onEvent;
	void*			m_associatedNode;
	bool			m_isEnabled;
	Type			m_type;
	
	EventListener();

	bool			init(Type eventType, std::string listenerID, const EventCallBack& onEvent);
};