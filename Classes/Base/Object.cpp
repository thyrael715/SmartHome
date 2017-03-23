#include "Object.h"


Object::Object()
{

}

Object::~Object()
{
	unregisterAllEvent();
}

void Object::registerAllEvent()
{
	for (size_t i = 0; i < (size_t)(EventType::VOICE); i++)
	{
		registerEvent(EventType(i));
	}
}

void Object::registerEvent(Object::EventType eventType)
{
	if (m_eventMap.find(eventType) != m_eventMap.end())
		return;

	EventCallbackStruct eventStruct;

	auto invokeEvents = [=](Object::EventType t){
		for (auto& actEvent : m_eventMap.at(t).callbacks){
			actEvent();
		}
	};

	switch (eventType)
	{
	case EventType::MOUSE:
	{
		EventListenerMouse* elm = new EventListenerMouse();
		elm->onMousePressed = CALLBACK_1(Object::onMousePressed, this);
		elm->onMouseReleased = [=, &eventType](sf::Event e)
		{
			onMouseReleased(e);
			invokeEvents(eventType);
		};
		elm->onMouseMoved = CALLBACK_1(Object::onMouseMoved, this);
		elm->onMouseScrolled = CALLBACK_1(Object::onMouseScrolled, this);

		eventStruct.eventListener = elm;
		m_eventMap[eventType] = eventStruct;
		EventDispatcher::getInstance()->addEventListener(elm, this);

		break;
	}
	case EventType::KEYBOARD:
	{
		EventListenerKeyboard* elk = new EventListenerKeyboard();
		elk->onKeyPressed = CALLBACK_1(Object::onKeyPressed, this);
		elk->onKeyReleased = [=, &eventType](sf::Event e)
		{
			onKeyReleased(e);
			invokeEvents(eventType);
		};

		eventStruct.eventListener = elk;
		m_eventMap[eventType] = eventStruct;
		EventDispatcher::getInstance()->addEventListener(elk, this);

		break;
	}
	case EventType::VOICE:
	{
		// TODO: extend it
		break;
	}
	case EventType::UNKNOWN:
	default:
		break;
	}
}

void Object::unregisterAllEvent()
{
	for (size_t i = 0; i < (size_t)(EventType::VOICE); i++)
	{
		unregisterEvent(EventType(i));
	}
}

void Object::unregisterEvent(Object::EventType eventType)
{
	auto iter = m_eventMap.find(eventType);

	if (iter == m_eventMap.end())
		return;

	EventDispatcher::getInstance()->removeEventListener(iter->second.eventListener);
	delete iter->second.eventListener;
	m_eventMap.erase(iter);
}

void Object::addEvent(Object::EventType eventType, const std::function<void()>& func)
{
	if (m_eventMap.find(eventType) == m_eventMap.end())
		return;

	m_eventMap.at(eventType).callbacks.push_back(func);
}