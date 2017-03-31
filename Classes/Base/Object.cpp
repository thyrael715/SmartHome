#include "Object.h"


Object::Object()
	: m_zOrder(0)
{
	init();
}


Object::~Object()
{
	unregisterAllEvent();
	removeAllChildren();
}


void Object::init()
{
	// Base init code
}


bool Object::contains(const sf::Vector2f& point) const
{
	return true;
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


int Object::getZOrder() const
{
	return m_zOrder;
}


void Object::addChild(Object* obj, int zOrder)
{
	m_children.insert(std::pair<int, Object*>(zOrder, obj));
}


void Object::removeChild(Object* obj)
{
	for (auto it = m_children.begin(); it != m_children.end(); it++)
	{
		if (it->first == obj->m_zOrder && it->second == obj)
		{
			delete it->second;
			m_children.erase(it);
			break;
		}
	}
}


void Object::removeAllChildren()
{
	for (auto it = m_children.begin(); it != m_children.end(); it++)
	{
		delete it->second;
		it = m_children.erase(it);
	}

	m_children.clear();
}


std::multimap<int, Object*> Object::getChildren() const
{
	return m_children;
}


void Object::onDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	// Nothing to do here
}


void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Combine transforms
	states.transform *= getTransform();

	this->onDraw(target, states);

	for each (auto& item in m_children)
	{
		target.draw(*item.second, states);
	}
}