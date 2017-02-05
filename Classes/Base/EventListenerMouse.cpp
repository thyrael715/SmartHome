#include "EventListenerMouse.h"

#include <iostream>

const std::string EventListenerMouse::LISTENER_ID = "__listener_mouse";

EventListenerMouse::EventListenerMouse()
	: onMousePressed(nullptr)
	, onMouseReleased(nullptr)
	, onMouseScrolled(nullptr)
	, onMouseMoved(nullptr)
{
	init();
}

EventListenerMouse::~EventListenerMouse()
{

}


bool EventListenerMouse::init()
{
	auto listener = [this](sf::Event e)
	{
		switch (e.type)
		{
			case sf::Event::MouseButtonPressed:
			{
				if (onMousePressed != nullptr) { onMousePressed(e); }
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				if (onMouseReleased != nullptr) { onMouseReleased(e); }
				break;
			}
			case sf::Event::MouseWheelScrolled:
			{
				if (onMouseScrolled != nullptr) { onMouseScrolled(e); }
				break;
			}
			case sf::Event::MouseMoved:
			{
				if (onMouseMoved != nullptr) { onMouseMoved(e); }
				break;
			}
			default:
			{
				break;
			}
		}
	};

	if (EventListener::init(Type::MOUSE, LISTENER_ID, listener))
	{
		return true;
	}

	return false;
}