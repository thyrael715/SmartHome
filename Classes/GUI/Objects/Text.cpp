#include "Text.h"

void Text::onDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	target.draw(m_text, states);
}