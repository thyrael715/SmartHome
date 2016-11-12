#include "EventListenerMouse.h"

#include <iostream>

const std::string EventListenerMouse::LISTENER_ID = "__listener_mouse";

EventListenerMouse::EventListenerMouse()
	: onMousePressed(nullptr)
	, onMouseReleased(nullptr)
	, onMouseScroll(nullptr)
{

}

EventListenerMouse::~EventListenerMouse()
{

}

EventListenerMouse* EventListenerMouse::create()
{
	auto ret = new (std::nothrow) EventListenerMouse();

	if (ret)
	{
		ret->init();
	}

	return ret;
}

bool EventListenerMouse::init()
{
	auto listener = [this](sf::Event e)
	{
		if (e.type == sf::Event::MouseButtonPressed)
		{
			if (onMousePressed != nullptr)
			{
				onMousePressed(e);
			}
		}
		else if (e.type == sf::Event::MouseButtonReleased)
		{
			if (onMouseReleased != nullptr)
			{
				onMouseReleased(e);
			}
		}
	};

	if (EventListener::init(Type::MOUSE, LISTENER_ID, listener))
	{
		return true;
	}

	return false;
}