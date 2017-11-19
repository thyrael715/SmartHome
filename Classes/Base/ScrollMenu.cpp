#include "ScrollMenu.h"


ScrollMenu::ScrollMenu(MenuOrientation orientation, bool isDoubleClickSupport)
	: Menu(orientation, isDoubleClickSupport)
	, m_scrollView(nullptr)
	, m_background(nullptr)
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
	this->addChild(m_background);

	// ScrollView
	auto size = m_background->getSize();
	m_scrollView = new sf::View(sf::FloatRect(getPosition().x, getPosition().y, size.x, size.y));
	m_scrollView->setViewport(sf::FloatRect(getPosition().x / WINDOW_WIDTH, getPosition().y / WINDOW_HEIGHT, size.x / WINDOW_WIDTH, size.y / WINDOW_HEIGHT));

	Scheduler::getInstance()->scheduleUpdate(this);
}


void ScrollMenu::onMousePressed(sf::Event e)
{
	if (m_background &&
		m_background->contains(sf::Vector2f((float)(e.mouseButton.x), (float)(e.mouseButton.y))))
	{
		Menu::onMousePressed(e);
	}
}


void ScrollMenu::onMouseReleased(sf::Event e)
{
	if (m_background &&
		m_background->contains(sf::Vector2f((float)(e.mouseButton.x), (float)(e.mouseButton.y))))
	{
		Menu::onMouseReleased(e);
	}
}


void ScrollMenu::onUpdate(float dt)
{
	// update scroll view
	// ScrollView cannot be add as a child to anything

	const sf::Vector2f position = convertToWorldSpace(getPosition());
	const sf::Vector2f size = (m_background) ? m_background->getSize() : ZERO;

	m_scrollView->setCenter(position.x + size.x / 2, position.y + size.y / 2);
	m_scrollView->setSize(sf::Vector2f(size.x, size.y));

	m_scrollView->setViewport(sf::FloatRect(position.x / WINDOW_WIDTH,
		position.y / WINDOW_HEIGHT,
		size.x / WINDOW_WIDTH,
		size.y / WINDOW_HEIGHT));
}


void ScrollMenu::onBeforeDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	target.setView(*m_scrollView);
}


void ScrollMenu::onAfterDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	target.setView(target.getDefaultView());
}


void ScrollMenu::setSize(const sf::Vector2f& size)
{
	m_background->setSize(size);
	onUpdate(0);
}


sf::Vector2f ScrollMenu::getSize() const
{
	if (m_background)
		return m_background->getSize();

	return ZERO;
}


void ScrollMenu::setFillColor(const sf::Color& color)
{
	if (m_background)
		m_background->setFillColor(color);
}


sf::Color ScrollMenu::getFillColor() const
{
	if (m_background)
		return m_background->getFillColor();

	return COLOR_TRANSPARENT;
}