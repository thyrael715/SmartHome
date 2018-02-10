#pragma once

#include "Menu.h"
#include "Slider.h"


class ScrollMenu : public Menu
{
public:
	ScrollMenu(Orientation orientation, bool isDoubleClickSupport = false);
	virtual ~ScrollMenu();

	void init();

	void setSize(const sf::Vector2f& size);
	sf::Vector2f getSize() const;
	sf::Vector2f getSizeWithoutScrollBar() const;
	void setBackgroundColor(const sf::Color& color);

public:

	virtual void onUpdate(float dt) override;

protected:

	virtual void onBeforeDraw(sf::RenderTarget& target, sf::RenderStates& states) const;
	virtual void onAfterDraw(sf::RenderTarget& target, sf::RenderStates& states) const;

private:

	sf::Vector2f m_size;
	sf::View* m_scrollView;
	RectangleShape* m_background;
	Slider* m_slider;
};