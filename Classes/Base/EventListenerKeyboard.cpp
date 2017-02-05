#include "EventListenerKeyboard.h"

#include <iostream>

const std::string EventListenerKeyboard::LISTENER_ID = "__listener_keyboard";

EventListenerKeyboard::EventListenerKeyboard()
	: onKeyPressed(nullptr)
	, onKeyReleased(nullptr)
{
	init();
}

EventListenerKeyboard::~EventListenerKeyboard()
{

}


bool EventListenerKeyboard::init()
{
	auto listener = [this](sf::Event e)
	{
		switch (e.type)
		{
		case sf::Event::KeyPressed:
		{
			if (onKeyPressed != nullptr) { onKeyPressed(e); }
			break;
		}
		case sf::Event::KeyReleased:
		{
			if (onKeyReleased != nullptr) { onKeyReleased(e); }
			break;
		}
		default:
		{
			break;
		}
		}
	};

	if (EventListener::init(Type::KEYBOARD, LISTENER_ID, listener))
	{
		return true;
	}

	return false;
}