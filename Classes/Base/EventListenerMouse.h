#pragma once

#include "EventListener.h"

class EventListenerMouse : public EventListener
{
public:

	static const std::string LISTENER_ID;

	virtual ~EventListenerMouse();
	static EventListenerMouse* create();

	EventCallBack onMousePressed;
	EventCallBack onMouseReleased;
	EventCallBack onMouseScroll;

protected:

	EventListenerMouse();
	bool init();
};