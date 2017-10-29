#pragma once

#include "MenuItem.h"


class Menu : public Object
{
public:

	enum MenuOrientation
	{
		HORIZONTAL,
		VERTICAL
	};

	Menu(MenuOrientation orientation, bool isDoubleClickSupport = false);
	virtual ~Menu();
	void init();

	virtual void addChild(Object* obj, int zOrder = 0) override;
	void setOrientation(MenuOrientation orientation);

protected:

	virtual void onMousePressed(sf::Event e) override;
	virtual void onMouseReleased(sf::Event e) override;

protected:

	bool isMenuItem(Object* obj) const;

	void alignMenuItem(MenuItem* item);
	void alignMenuItemHorizontally(MenuItem* item);
	void alignMenuItemVertically(MenuItem* item);

	MenuItem* getMenuItemForClick(int x, int y) const;

protected:
		
	MenuItem* m_selectedItem;
	MenuItem* m_activatedItem;

private:

	void activationProcess(MenuItem* selectedItem);
	void selectionProcess(MenuItem* selectedItem);

private:

	sf::Event::MouseButtonEvent m_prevClick;
	MenuOrientation m_orientation;
	float m_spaceBetweenItems;
	bool m_isDoubleClickSupport;
	sf::Clock m_clock;
};