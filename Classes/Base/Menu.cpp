#include "Menu.h"


Menu::Menu(Orientation orientation, bool isDoubleClickSupport)
	: m_selectedItem(nullptr)
	, m_activatedItem(nullptr)
	, m_orientation(orientation)
	, m_spaceBetweenItems(1.0f)
	, m_isDoubleClickSupport(isDoubleClickSupport)
	, m_menuitemLayer(nullptr)
{
	init();
}


Menu::~Menu()
{
	m_selectedItem = nullptr;
	m_activatedItem = nullptr;
}


void Menu::init()
{
	m_menuitemLayer = new Object();
	this->addChild(m_menuitemLayer);

	registerEvent(EventType::MOUSE);
}


void Menu::addChild(Object* obj, int zOrder)
{
	// Menu only supports menuitems
	if (MenuItem* item = dynamic_cast<MenuItem*>(obj))
	{
		alignMenuItem(item);
		m_menuitemLayer->addChild(obj, zOrder);
	}
	else
	{		
		Object::addChild(obj, zOrder);
	}
}


void Menu::onMousePressed(sf::Event e)
{
	if (e.mouseButton.button != sf::Mouse::Left || !m_isDoubleClickSupport)
		return;

	// If we clicked on a menuitem
	if (MenuItem* actSelectedItem = getMenuItemForClick(e.mouseButton.x, e.mouseButton.y))
	{
		// lambda function for double click
		std::function<bool()> isDoubleClick = [=]()
		{
			const unsigned short maxDistance = 10;
			sf::Vector2f pointA((float)(e.mouseButton.x), (float)(e.mouseButton.y));
			sf::Vector2f pointB((float)(m_prevClick.x), (float)(m_prevClick.y));

			if (Maths::getDistance(pointA, pointB) < maxDistance && m_selectedItem == actSelectedItem)
			{
				const float maxClickTimeDiff = 0.5f;

				if (m_clock.getElapsedTime().asSeconds() <= maxClickTimeDiff)
				{
					m_prevClick.x = 0;
					m_prevClick.y = 0;

					return true;
				}
			}
			else
			{
				m_prevClick = e.mouseButton;
			}

			return false;
		};

		// Mouse click handling

		// Single click
		selectionProcess(actSelectedItem);

		if (isDoubleClick())
		{
			// Double click
			activationProcess(actSelectedItem);
		}

		m_clock.restart();
	}
}


void Menu::onMouseReleased(sf::Event e)
{
	if (e.mouseButton.button != sf::Mouse::Left || m_isDoubleClickSupport)
		return;

	if (MenuItem* item = getMenuItemForClick(e.mouseButton.x, e.mouseButton.y))
	{
		activationProcess(item);
	}		
}


void Menu::activationProcess(MenuItem* selectedItem)
{
	if (m_activatedItem && m_activatedItem->onDeactivate != nullptr)
		m_activatedItem->onDeactivate();

	m_activatedItem = selectedItem;

	if (m_activatedItem && m_activatedItem->onActivate != nullptr)
		m_activatedItem->onActivate();
}


void Menu::selectionProcess(MenuItem* selectedItem)
{
	if (m_selectedItem && m_selectedItem->onUnselect != nullptr)
		m_selectedItem->onUnselect();

	m_selectedItem = selectedItem;

	if (m_selectedItem && m_selectedItem->onSelect != nullptr)
		m_selectedItem->onSelect();
}


MenuItem* Menu::getMenuItemForClick(int x, int y) const
{
	for each (auto child in m_menuitemLayer->getChildren())
	{
		if (child->contains(sf::Vector2f((float)x, (float)y)))
		{
			return dynamic_cast<MenuItem*>(child);
		}
	}

	return nullptr;
}


void Menu::alignMenuItem(MenuItem* item)
{
	switch (m_orientation)
	{
	case HORIZONTAL:
	{
		alignMenuItemHorizontally(item);
		break;
	}
	case VERTICAL:
	{
		alignMenuItemVertically(item);
		break;
	}
	default:
		break;
	}
}


void Menu::alignMenuItemHorizontally(MenuItem* item)
{
	auto childrenNum = m_menuitemLayer->getChildren().size();
	auto newPosX = childrenNum * (item->getGlobalBounds().width + m_spaceBetweenItems);

	item->move(newPosX, 0.0f);
}


void Menu::alignMenuItemVertically(MenuItem* item)
{
	auto childrenNum = m_menuitemLayer->getChildren().size();
	auto newPosY = childrenNum * (item->getGlobalBounds().height + m_spaceBetweenItems);

	item->move(0.0f, newPosY);
}


void Menu::setOrientation(Orientation orientation)
{
	m_orientation = orientation;
	// TODO: realign the menuitems based on orientation
}


MenuItem* Menu::getSelectedItem() const
{
	return m_selectedItem;
}


MenuItem* Menu::getActivatedItem() const
{
	return m_activatedItem;
}


