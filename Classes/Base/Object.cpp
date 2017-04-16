#include "Object.h"


Object::Object()
	: m_zOrder(0)
	, m_parent(nullptr)
{

}


Object::~Object()
{
	unregisterAllEvent();
	removeAllChildren();
}


bool Object::contains(const sf::Vector2f& point) const
{
	for each (auto item in m_children)
	{
		if (item.second->contains(point))
		{
			return true;
		}
	}

	return false;
}


sf::FloatRect Object::getGlobalBounds() const
{
	if (m_children.empty())
	{
		return sf::FloatRect(0, 0, 0, 0);
	}

	sf::FloatRect boundingBox(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);

	for each (auto item in m_children)
	{
		sf::FloatRect actChildBounds = item.second->getGlobalBounds();
		
		if (actChildBounds.left < boundingBox.left)
		{
			boundingBox.left = actChildBounds.left;
		}
		if (actChildBounds.top < boundingBox.top)
		{
			boundingBox.top = actChildBounds.top;
		}
		if (actChildBounds.width > boundingBox.width)
		{
			boundingBox.width = actChildBounds.width;
		}
		if (actChildBounds.height > boundingBox.height)
		{
			boundingBox.height = actChildBounds.height;
		}
	}

	boundingBox.width -= boundingBox.left;
	boundingBox.height -= boundingBox.top;

	return boundingBox;
}


void Object::registerAllEvent()
{
	for (size_t i = 0; i < (size_t)(EventType::UNKNOWN); ++i)
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
		elm->onMouseReleased = [=](sf::Event e)
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
		elk->onKeyReleased = [=](sf::Event e)
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
	for (size_t i = 0; i < (size_t)(EventType::UNKNOWN); ++i)
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


sf::Vector2f Object::convertToWorldSpace(const sf::Vector2f& point) const
{
	sf::Vector2f res(point);

	Object* actParent = m_parent;

	while (actParent != nullptr)
	{
		res += actParent->getPosition();
		actParent = actParent->getParent();
	}

	return res;
}


sf::Vector2f Object::convertToObjectSpace(const sf::Vector2f& point) const
{
	return point - convertToWorldSpace(getPosition());
}


void Object::setParent(Object* obj)
{
	m_parent = obj;
}


Object* Object::getParent() const
{
	return m_parent;
}


void Object::addChild(Object* obj, int zOrder)
{
	m_children.insert(std::pair<int, Object*>(zOrder, obj));
	obj->setParent(this);
}


void Object::removeChild(Object* obj)
{
	for (auto it = m_children.begin(); it != m_children.end(); ++it)
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
	for (auto it = m_children.begin(); it != m_children.end();)
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


void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Combine transforms
	states.transform *= getTransform();

	this->onDraw(target, states);

	for (auto& it = m_children.rbegin(); it != m_children.rend(); ++it)
	{
		target.draw(*it->second, states);
	}
}