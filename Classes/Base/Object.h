#pragma once

#include "EventDispatcher.h"
#include "Defaults.h"
#include <list>


class Object : public sf::Transformable
{
	enum EventType
	{
		UNKNOWN = -1,
		MOUSE = 0,
		KEYBOARD = 1,
		VOICE = 2
	};

	struct EventCallbackStruct
	{
		EventListener* eventListener;
		std::vector<std::function<void()>> callbacks;
	};

public:

	Object();
	virtual ~Object();
	virtual bool contains(const sf::Vector2f& point) const = 0;

	void registerAllEvent();
	void registerEvent(EventType type);
	void unregisterAllEvent();
	void unregisterEvent(EventType type);

	void addEvent(EventType eventType, const std::function<void()>& func);
	
protected:

	virtual void onMousePressed(sf::Event e) {};
	virtual void onMouseReleased(sf::Event e) {};
	virtual void onMouseScrolled(sf::Event e) {};
	virtual void onMouseMoved(sf::Event e) {};

	virtual void onKeyPressed(sf::Event e) {};
	virtual void onKeyReleased(sf::Event e) {};
	
private:

	std::map<EventType, EventCallbackStruct> m_eventMap;
};