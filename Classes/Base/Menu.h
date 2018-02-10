#pragma once

#include "MenuItem.h"
#include "RectangleShape.h"


class Menu : public Object
{
public:

	Menu(Orientation orientation, bool isDoubleClickSupport = false);
	virtual ~Menu();
	void init();

	virtual void addChild(Object* obj, int zOrder = 0) override;
	void setOrientation(Orientation orientation);

	MenuItem* getSelectedItem() const;
	MenuItem* getActivatedItem() const;

protected:

	virtual void onMousePressed(sf::Event e) override;
	virtual void onMouseReleased(sf::Event e) override;
	
	void alignMenuItem(MenuItem* item);
	void alignMenuItemHorizontally(MenuItem* item);
	void alignMenuItemVertically(MenuItem* item);

	MenuItem* getMenuItemForClick(int x, int y) const;
	
private:

	void activationProcess(MenuItem* selectedItem);
	void selectionProcess(MenuItem* selectedItem);
	
protected:

	sf::Event::MouseButtonEvent m_prevClick;
	Orientation m_orientation;
	float m_spaceBetweenItems;
	bool m_isDoubleClickSupport;
	sf::Clock m_clock;

	Object* m_menuitemLayer;

	MenuItem* m_selectedItem;
	MenuItem* m_activatedItem;
};


