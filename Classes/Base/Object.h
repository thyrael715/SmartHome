#pragma once

#include "EventDispatcher.h"
#include "Scheduler.h"
#include "Defaults.h"


class Object : public sf::Drawable, public sf::Transformable
{

	struct EventCallbackStruct
	{
		EventListener* eventListener;
		std::vector<std::function<void()>> callbacks;
	};

public:

	enum EventType
	{
		MOUSE = 0,
		KEYBOARD = 1,
		VOICE = 2,
		UNKNOWN = 3,
	};

	Object();
	virtual ~Object();

	virtual bool contains(const sf::Vector2f& point) const;
	virtual sf::FloatRect getGlobalBounds() const;
	virtual void onUpdate(float dt){};

	void registerAllEvent();
	void registerEvent(EventType type);
	void unregisterAllEvent();
	void unregisterEvent(EventType type);

	void addEvent(EventType eventType, const std::function<void()>& func);

	sf::Vector2f convertToWorldSpace(const sf::Vector2f& point) const;
	sf::Vector2f convertToObjectSpace(const sf::Vector2f& point) const;

	void setParent(Object* obj);
	Object* getParent() const;

	void addChild(Object* obj, int zOrder = 0);
	void removeChild(Object* obj);
	void removeAllChildren();
	std::multimap<int, Object*> getChildren() const;
	
protected:

	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates& states) const {};

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
	Object* m_parent;
	int m_zOrder;
};