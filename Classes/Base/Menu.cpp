#include "Menu.h"




Menu::Menu(MenuOrientation orientation, bool isDoubleClickSupport)
	: m_selectedItem(nullptr)
	, m_activatedItem(nullptr)
	, m_orientation(orientation)
	, m_spaceBetweenItems(1.0f)
	, m_isDoubleClickSupport(isDoubleClickSupport)
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
	registerEvent(EventType::MOUSE);
}


void Menu::addChild(Object* obj, int zOrder)
{
	// Menu only supports menuitems
	MenuItem* item = dynamic_cast<MenuItem*>(obj);
	if (item)
	{
		this->alignMenuItem(item);
	}

	Object::addChild(obj, zOrder);
}


void Menu::onMousePressed(sf::Event e)
{
	if (e.mouseButton.button != sf::Mouse::Left || !m_isDoubleClickSupport)
		return;

	MenuItem* actSelectedItem = getMenuItemForClick(e.mouseButton.x, e.mouseButton.y);
	
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


void Menu::onMouseReleased(sf::Event e)
{
	if (e.mouseButton.button != sf::Mouse::Left || m_isDoubleClickSupport)
		return;

	MenuItem* actSelectedItem = getMenuItemForClick(e.mouseButton.x, e.mouseButton.y);
	activationProcess(actSelectedItem);
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
	for each (Object* child in m_children)
	{
		MenuItem* item = dynamic_cast<MenuItem*>(child);
		if (item && item->contains(sf::Vector2f((float)x, (float)y)))
		{
			return item;
		}
	}

	return nullptr;
}


void Menu::alignMenuItem(MenuItem* item)
{
	switch (m_orientation)
	{
	case Menu::HORIZONTAL:
	{
		alignMenuItemHorizontally(item);
		break;
	}
	case Menu::VERTICAL:
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
	auto newPosX = 0.0f;

	for each (auto child in m_children)
	{
		if (child != item && isMenuItem(child))
		{
			newPosX += (child->getGlobalBounds().width + m_spaceBetweenItems);
		}
	}

	item->setPosition(newPosX, item->getPosition().y);
}


void Menu::alignMenuItemVertically(MenuItem* item)
{
	auto newPosY = 0.0f;

	for each (auto child in m_children)
	{
		if (child != item && isMenuItem(child))
		{
			newPosY += (child->getGlobalBounds().height + m_spaceBetweenItems);
		}
	}

	item->setPosition(item->getPosition().x, newPosY);
}


void Menu::setOrientation(MenuOrientation orientation)
{
	m_orientation = orientation;
	// TODO: realign the menuitems based on orientation
}


bool Menu::isMenuItem(Object* obj) const
{
	if (!obj)
		return false;

	return dynamic_cast<MenuItem*>(obj) != nullptr;
}