#include "Text.h"


bool Text::contains(const sf::Vector2f& point) const
{
	auto newPoint = convertToObjectSpace(point);
	auto rect = m_text.getLocalBounds();

	return Maths::isInRect(rect, newPoint);
}


void Text::onDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	target.draw(m_text, states);
}

