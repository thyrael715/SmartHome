#pragma once

#include "EventDispatcher.h"
#include "Defaults.h"
#include "Scheduler.h"


class Object : public sf::Drawable, public sf::Transformable
{
	enum EventType
	{
		UNKNOWN = -1,
		MOUSE = 0,
		KEYBOARD = 1,
		VOICE = 2
	};

	struct EventCallbackStruct
	{
		EventListener* eventListener;
		std::vector<std::function<void()>> callbacks;
	};

public:

	Object();
	virtual ~Object();
	virtual void init();
	virtual bool contains(const sf::Vector2f& point) const;
	virtual void onUpdate(float dt){};

	void registerAllEvent();
	void registerEvent(EventType type);
	void unregisterAllEvent();
	void unregisterEvent(EventType type);

	void addEvent(EventType eventType, const std::function<void()>& func);

	void setZOrder(int zOrder);
	int getZOrder() const;

	void addChild(Object* obj, int zOrder = 0);
	void removeChild(Object* obj);
	void removeAllChildren();
	std::multimap<int, Object*> getChildren() const;
	
protected:

	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates& states) const;

	virtual void onMousePressed(sf::Event e) {};
	virtual void onMouseReleased(sf::Event e) {};
	virtual void onMouseScrolled(sf::Event e) {};
	virtual void onMouseMoved(sf::Event e) {};

	virtual void onKeyPressed(sf::Event e) {};
	virtual void onKeyReleased(sf::Event e) {};

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:

	std::map<EventType, EventCallbackStruct> m_eventMap;
	std::multimap<int, Object*> m_children;
	int m_zOrder;
};