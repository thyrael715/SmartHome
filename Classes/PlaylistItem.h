#pragma once

#include "Text.h"
#include "AudioFile.h"
#include "RectangleShape.h"


enum SelectionState
{
	SELECTIONSTATE_UNSELECTED,
	SELECTIONSTATE_PRESELECTED,
	SELECTIONSTATE_SELECTED
};


class PlaylistItem : public AudioFile, public RectangleShape
{
public:


	PlaylistItem(const sf::String& path);
	virtual ~PlaylistItem();

	Text* getSongNameText() const;
	Text* getDurationText() const;

	SelectionState getSelectionState() const;
	void setSelectionState(SelectionState state);

public:

	virtual void onUpdate(float dt) override;
	
protected:

	virtual void onMousePressed(sf::Event e) override;
	
private:

	void init();
	void setTextsFillColor(sf::Color color);

	void updateColors();
	void updateTextsPosiiton();
	
private:

	Text* m_songNameText;
	Text* m_durationText;

	sf::Font* m_font;	
	sf::Clock m_clock;

	SelectionState m_selectionState;
};