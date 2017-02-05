#pragma once

#include "EventListener.h"

class EventListenerKeyboard : public EventListener
{
public:

	static const std::string LISTENER_ID;

	EventListenerKeyboard();
	virtual ~EventListenerKeyboard();

	EventCallBack onKeyPressed;
	EventCallBack onKeyReleased;

protected:

	bool init();
};