#pragma once

#include "EventListener.h"
#include <vector>
#include <unordered_map>

#include "EventListenerMouse.h"



class Object;

class EventDispatcher
{
public:

	virtual ~EventDispatcher();

	static EventDispatcher* getInstance();

	void addEventListener(EventListener* listener, Object* obj);
	void removeEventListener(EventListener* listener);
	std::vector<EventListener*>* getListeners(const std::string listenerID) const;

	void handleEvent(sf::Event e);
	void handleEventMouse(sf::Event e);
	void handleEventKeyboard(sf::Event e);
	void handleEventVoice();
	
private:

	std::unordered_map<std::string, std::vector<EventListener*>* >  m_listenerMap;

	explicit EventDispatcher();
	EventDispatcher(const EventDispatcher&) = delete;
	EventDispatcher* operator=(const EventDispatcher&) = delete;
};