#include "Object.h"


Object::Object()
	: m_zOrder(0)
	, m_parent(nullptr)
{

}


Object::~Object()
{
	removeAllChildren();
}


bool Object::contains(const sf::Vector2f& point) const
{
	for each (auto child in m_children)
	{
		if (child->contains(point))
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

	for each (auto child in m_children)
	{
		sf::FloatRect actChildBounds = child->getGlobalBounds();
		
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

	m_eventMap.clear();
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
	if (obj)
	{
		bool isInserted = false;
		obj->setZOrder(zOrder);
		obj->setParent(this);

		for (auto it = m_children.cbegin(); it != m_children.cend(); ++it)
		{
			if ((*it)->getZOrder() < zOrder)
			{
				if (it == m_children.cbegin())
				{
					m_children.push_front(obj);
					isInserted = true;
					break;
				}
				else
				{
					m_children.insert(it - 1, obj);
					isInserted = true;
					break;
				}
			}
		}

		if (!isInserted)
		{
			m_children.push_back(obj);
		}
	}
}


void Object::removeChild(Object* obj)
{
	for (auto it = m_children.begin(); it != m_children.end(); ++it)
	{
		if (*it == obj)
		{
			delete *it;
			m_children.erase(it);
			break;
		}
	}
}


void Object::removeAllChildren()
{
	for (auto it = m_children.begin(); it != m_children.end(); ++it)
	{
		delete *it;
	}

	m_children.clear();
}


std::deque<Object*> Object::getChildren() const
{
	return m_children;
}


void Object::setZOrder(int zOrder)
{
	m_zOrder = zOrder;
}


int Object::getZOrder() const
{
	return m_zOrder;
}


void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Combine transforms
	states.transform *= getTransform();

	// Call object's own unique draw method 
	this->onDraw(target, states);
	
	for (auto child : m_children)
	{
		target.draw(*child, states);
	}

	//if (Defaults::getInstance()->getMainView().getSize() != target.getView().getSize() ||
	//	Defaults::getInstance()->getMainView().getCenter() != target.getView().getCenter())
	//{
	//	target.setView(Defaults::getInstance()->getMainView());
	//}
}