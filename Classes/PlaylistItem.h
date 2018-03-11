#pragma once

#include "Text.h"
#include "AudioFile.h"
#include "MenuItem.h"
#include "RectangleShape.h"


class PlaylistItem : public AudioFile, public MenuItem
{
public:
	
	PlaylistItem(const std::string& path);
	virtual ~PlaylistItem();

	void setSize(const sf::Vector2f& size);
	void setSize(const float width, const float height);
	sf::Vector2f getSize() const;

private:

	void init();
	void initCallbacks();
	void setTextsFillColor(sf::Color color);

	void updateTextsPosition();
	void updateSongNameLength();
	
private:

	RectangleShape* m_background;

	Text* m_songNameText;
	Text* m_durationText;

	sf::Font* m_font;	
	sf::Vector2f m_size;
	static size_t m_instanceCounter;
};