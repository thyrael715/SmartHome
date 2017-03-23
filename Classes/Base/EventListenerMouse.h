#pragma once

#include "EventListener.h"

class EventListenerMouse : public EventListener
{
public:

	static const std::string LISTENER_ID;

	EventListenerMouse();
	virtual ~EventListenerMouse();

	EventCallBack onMousePressed;
	EventCallBack onMouseReleased;
	EventCallBack onMouseScrolled;
	EventCallBack onMouseMoved;

protected:

	bool init();
};