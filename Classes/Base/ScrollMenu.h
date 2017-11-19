#pragma once

#include "Menu.h"


class ScrollMenu : public Menu
{
public:
	ScrollMenu(MenuOrientation orientation, bool isDoubleClickSupport = false);
	virtual ~ScrollMenu();

	void init();

	void setSize(const sf::Vector2f& size);
	sf::Vector2f getSize() const;
	void setFillColor(const sf::Color& color);
	sf::Color getFillColor() const;

public:

	virtual void onUpdate(float dt);
	virtual void onMousePressed(sf::Event e) override;
	virtual void onMouseReleased(sf::Event e) override;

protected:

	virtual void onBeforeDraw(sf::RenderTarget& target, sf::RenderStates& states) const;
	virtual void onAfterDraw(sf::RenderTarget& target, sf::RenderStates& states) const;

private:

	sf::View* m_scrollView;
	RectangleShape* m_background;
};