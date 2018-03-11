#include "ScrollMenu.h"


#define SM_SCROLLSPEED 30


ScrollMenu::ScrollMenu(Orientation orientation, bool isDoubleClickSupport)
	: Menu(orientation, isDoubleClickSupport)
	, m_size(ZERO)
	, m_scrollView(nullptr)
	, m_background(nullptr)
	, m_slider(nullptr)
{
	init();
}


ScrollMenu::~ScrollMenu()
{
	SAFE_DELETE(m_scrollView);
}


void ScrollMenu::init()
{
	m_background = new RectangleShape();
	m_background->setFillColor(COLOR_TRANSPARENT);
	this->addChild(m_background, 1);

	// ScrollView
	auto size = m_background->getSize();
	m_scrollView = new sf::View(sf::FloatRect(getPosition().x, getPosition().y, size.x, size.y));
	m_scrollView->setViewport(sf::FloatRect(getPosition().x / WINDOW_WIDTH, getPosition().y / WINDOW_HEIGHT, size.x / WINDOW_WIDTH, size.y / WINDOW_HEIGHT));

	// TODO: rework size should NOT be in contructor -> size of slider will be fix
	m_slider = new Slider(m_orientation);
	m_slider->setScrollableArea(m_size);
	m_slider->setObjectToBeScrolled(m_menuitemLayer);
	m_slider->setScrollSpeed(SM_SCROLLSPEED);
	this->addChild(m_slider);

	Scheduler::getInstance()->scheduleUpdate(this);
	registerEvent(EventType::MOUSE);
}


void ScrollMenu::onUpdate(float dt)
{
	// update scroll view
	// ScrollView cannot be add as a child to anything

	const sf::Vector2f position = convertToWorldSpace(getPosition());

	m_scrollView->setCenter(position.x + m_size.x / 2, position.y + m_size.y / 2);
	m_scrollView->setSize(sf::Vector2f(m_size.x, m_size.y));

	m_scrollView->setViewport(sf::FloatRect(position.x / WINDOW_WIDTH,
		position.y / WINDOW_HEIGHT,
		m_size.x / WINDOW_WIDTH,
		m_size.y / WINDOW_HEIGHT));
}


void ScrollMenu::onBeforeDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	target.setView(*m_scrollView);
}


void ScrollMenu::onAfterDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	target.setView(target.getDefaultView());
}


void ScrollMenu::onMouseScrolled(sf::Event e)
{
	if (m_menuitemLayer &&
		m_menuitemLayer->getGlobalBounds().height > m_background->getSize().y)
	{
		// align delegate object
		float newPosY = e.mouseWheelScroll.delta * SM_SCROLLSPEED;
		float minY = -1 * (m_menuitemLayer->getGlobalBounds().height - m_size.y);
		float maxY = 0.0f;

		// Scrolling to the bottom of the delegate object
		if (m_menuitemLayer->getPosition().y + newPosY <= minY)
		{
			m_menuitemLayer->setPosition(sf::Vector2f(m_menuitemLayer->getPosition().x, minY));
		}
		// Scrolling to the top of the delegate object
		else if (m_menuitemLayer->getPosition().y + newPosY >= maxY)
		{
			m_menuitemLayer->setPosition(sf::Vector2f(m_menuitemLayer->getPosition().x, maxY));
		}
		// Otherwise just move the object to be scrolled
		else
		{
			m_menuitemLayer->move(0.0f, newPosY);
		}

		// update the position of Slider's indicator
		if (m_slider)
		{
			m_slider->updateIndicatorPos();
		}
	}
}


bool ScrollMenu::contains(const sf::Vector2f& point) const
{
	return m_background->contains(point);
}


void ScrollMenu::setSize(const sf::Vector2f& size)
{
	m_size = size;

	//update background size
	m_background->setSize(sf::Vector2f(m_size.x, m_size.y));

	// update slider size
	m_slider->setScrollableArea(m_size);

	onUpdate(0);
}


sf::Vector2f ScrollMenu::getSize() const
{
	return m_size;
}


sf::Vector2f ScrollMenu::getSizeWithoutScrollBar() const
{
	sf::Vector2f size(m_size);

	if (m_orientation == HORIZONTAL)
	{
		size.y -= m_slider->getSize().y;
	}
	else
	{
		size.x -= m_slider->getSize().x;
	}

	return size;
}


void ScrollMenu::setBackgroundColor(const sf::Color& color)
{
	if (m_background)
	{
		m_background->setFillColor(color);
	}
}