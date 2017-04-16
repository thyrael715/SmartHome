#pragma once

#include "Object.h"

/*
 * Adapter class for Text
 */
class Text : public Object
{
public:

	Text() : m_text(){};
	Text(const sf::String& string, const sf::Font& font, unsigned int characterSize = 30) : m_text(string, font, characterSize){};

	void setString(const sf::String& string)				{ m_text.setString(string); };
	void setFont(const sf::Font& font)						{ m_text.setFont(font); };
	void setCharacterSize(unsigned int size)				{ m_text.setCharacterSize(size); };
	void setStyle(sf::Uint32 style)							{ m_text.setStyle(style); };
	void setFillColor(const sf::Color& color)				{ m_text.setFillColor(color); };
	void setOutlineColor(const sf::Color& color)			{ m_text.setOutlineColor(color); };
	void setOutlineThickness(float thickness)				{ m_text.setOutlineThickness(thickness); };

	const sf::String& getString() const						{ return m_text.getString(); };
	const sf::Font* getFont() const							{ return m_text.getFont(); };
	unsigned int getCharacterSize() const					{ return m_text.getCharacterSize(); };
	sf::Uint32 getStyle() const								{ return m_text.getStyle(); };
	const sf::Color& getFillColor() const					{ return m_text.getFillColor(); };
	const sf::Color& getOutlineColor() const				{ return m_text.getOutlineColor(); };
	float getOutlineThickness() const						{ return m_text.getOutlineThickness(); };
	sf::Vector2f findCharacterPos(std::size_t index) const	{ return m_text.findCharacterPos(index); };
	sf::FloatRect getLocalBounds() const					{ return m_text.getLocalBounds(); };
	sf::FloatRect getGlobalBounds() const					{ return m_text.getGlobalBounds(); };

protected:

	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates& states) const override;

private:

	sf::Text m_text;
};