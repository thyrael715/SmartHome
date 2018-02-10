#include "EventDispatcher.h"
#include "Maths.h"
#include "Object.h"

EventDispatcher::EventDispatcher()
{

}

EventDispatcher::~EventDispatcher()
{

}

EventDispatcher* EventDispatcher::getInstance()
{
	static EventDispatcher* ed = new EventDispatcher();
	return ed;
}

void EventDispatcher::addEventListener(EventListener* listener, Object* obj)
{
	std::vector<EventListener*>* listenerVector = nullptr;
	listener->setAssociatedObject(obj);
	const std::string listenerID = listener->getListenerID();

	auto iter = m_listenerMap.find(listenerID);
	if (iter == m_listenerMap.end())
	{
		listenerVector = new std::vector<EventListener*>();
		m_listenerMap.insert(std::make_pair(listenerID, listenerVector));
	}
	else
	{
		listenerVector = iter->second;
	}

	listenerVector->push_back(listener);
}

void EventDispatcher::removeEventListener(EventListener* listener)
{
	if (listener == nullptr)
		return;

	const std::string listenerID = listener->getListenerID();
	auto iter = m_listenerMap.find(listenerID);

	if (iter != m_listenerMap.end())
	{
		auto listenerVector = iter->second;
		for (size_t i = 0; i < listenerVector->size(); ++i)
		{
			if (listener == (*listenerVector)[i])
			{
				listenerVector->erase(listenerVector->begin() + i);
				if (listenerVector->empty())
				{
					delete iter->second;
					m_listenerMap.erase(iter);
				}

				return;
			}
		}
	}
}

void EventDispatcher::triggerEventHandling(sf::Event e)
{
	switch (e.type)
	{
		// Mouse event handling
		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
		case sf::Event::MouseWheelScrolled:
		case sf::Event::MouseMoved:
		{
			handleEventMouse(e);
			break;
		}
		// Keyboard event handling
		case sf::Event::KeyPressed:
		case sf::Event::KeyReleased:
		{
			handleEventKeyboard(e);
			break;
		}		
		default:
		{
			break;
		}
	}
}

std::vector<EventListener*>* EventDispatcher::getListeners(const std::string listenerID) const
{
	auto iter = m_listenerMap.find(listenerID);
	
	if (iter != m_listenerMap.end())
	{
		return iter->second;
	}

	return nullptr;
}

void EventDispatcher::handleEventMouse(sf::Event e)
{
	auto listenerVector = getListeners(EventListenerMouse::LISTENER_ID);
	EventListener* maxZOrderedListener = nullptr;

	if (listenerVector == nullptr)
		return;
	
	// Iterates through all of the mouse listeners
	// and selects the clicked object which has the highest Z-order number.
	for each (auto& listener in *listenerVector)
	{
		if (maxZOrderedListener &&
			maxZOrderedListener->getAssociatedObject()->getZOrder() > listener->getAssociatedObject()->getZOrder())
		{
			continue;
		}

		if (listener->getAssociatedObject()->contains(sf::Vector2f(MOUSE_RELATIVE_POS)))
		{
			maxZOrderedListener = listener;
		}
	}

	if (maxZOrderedListener)
	{
		maxZOrderedListener->onEvent(e);
	}
}

void EventDispatcher::handleEventKeyboard(sf::Event e)
{
	// TODO: extend it
}

void EventDispatcher::handleEventVoice()
{
	// TODO: extend it
}