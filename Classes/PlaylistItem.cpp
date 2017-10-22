#include "PlaylistItem.h"


#define PI_TEXTCOLOR_SELECTED		sf::Color(50, 50, 200)
#define PI_TEXTCOLOR_NONSELECTED	sf::Color(40, 255, 255, 255)
#define PI_BACKGROUND_SELECTED		sf::Color(255, 50, 50, 200)
#define PI_BACKGROUND_NONSELECTED	COLOR_TRANSPARENT

#define PI_TEXT_MARGIN		1
#define PI_TEXT_FONTSIZE	12


PlaylistItem::PlaylistItem(const sf::String& path)
	: AudioFile(path)
	, m_songNameText(nullptr)
	, m_durationText(nullptr)
	, m_font(nullptr)
	, m_selectionState(SELECTIONSTATE_UNSELECTED)
{
	init();
	Scheduler::getInstance()->scheduleUpdate(this);
}


PlaylistItem::~PlaylistItem()
{

}


void PlaylistItem::init()
{
	m_font = new sf::Font();

	if (!m_font || !m_font->loadFromFile("Fonts\\arial.ttf"))
	{
		// error...
		return;
	}
	
	// Title text initialization

	m_songNameText = new Text(m_title.c_str(), *m_font, PI_TEXT_FONTSIZE);
	m_songNameText->setFillColor(PI_TEXTCOLOR_NONSELECTED);
	this->addChild(m_songNameText);

	// Song duration text initialization

	const float songDurationInSec = m_duration.asSeconds();

	std::string minutesInStr = ITOS((int)(songDurationInSec) / 60);
	std::string secondsInStr = ITOS((int)(songDurationInSec) % 60);

	// if seconds are in range of [1..9] then a '0' has to be inserted. ie.: 6:5 -> 6:05
	if (secondsInStr.size() == 1)
	{
		secondsInStr = "0" + secondsInStr;
	}

	std::string fullDurationStr = minutesInStr + ":" + secondsInStr;

	m_durationText = new Text(fullDurationStr.c_str(), *m_font);
	m_durationText->setFillColor(PI_TEXTCOLOR_NONSELECTED);
	this->addChild(m_durationText);

	// Playlist item initialization
	
	setFillColor(PI_BACKGROUND_NONSELECTED);
	setVolume(10.0f);

	// Resize

	const float heightScaler = 1.5f;

	sf::FloatRect songNameTextBounds = m_songNameText->getGlobalBounds();
	sf::FloatRect durationTextBounds = m_durationText->getGlobalBounds();
	
	setSize(sf::Vector2f(songNameTextBounds.width + durationTextBounds.width, heightScaler * PI_TEXT_FONTSIZE));
}


void PlaylistItem::setTextsFillColor(sf::Color color)
{
	if (m_songNameText && m_durationText)
	{
		m_songNameText->setFillColor(color);
		m_durationText->setFillColor(color);
	}
}


void PlaylistItem::onMousePressed(sf::Event e)
{
	// We only allow left mouse button
	if (e.mouseButton.button != sf::Mouse::Left)
		return;

	const float maxClickTimeDiff = 0.5f;

	std::cout << "\nm_clock.getElapsedTime().asSeconds() = " << m_clock.getElapsedTime().asSeconds();
	if (m_clock.getElapsedTime().asSeconds() <= maxClickTimeDiff)
	{
		std::cout << "\nSELECTIONSTATE_SELECTED";
		m_selectionState = SELECTIONSTATE_SELECTED;
	}
	else
	{
		std::cout << "\nSELECTIONSTATE_PRESELECTED";
		m_selectionState = SELECTIONSTATE_PRESELECTED;
	}

	updateColors();

	m_clock.restart();
}


void PlaylistItem::onUpdate(float dt)
{
	// Update texts based on the background's size

	updateTextsPosiiton();

	// Update Background and text colors based on the selection and audio states

	updateColors();
}


void PlaylistItem::updateColors()
{

	if (m_selectionState == SELECTIONSTATE_SELECTED)
	{
		setFillColor(PI_BACKGROUND_SELECTED);
		setTextsFillColor(PI_TEXTCOLOR_SELECTED);
	}
	else if (m_selectionState == SELECTIONSTATE_PRESELECTED)
	{
		setFillColor(PI_BACKGROUND_SELECTED);
		setTextsFillColor(PI_TEXTCOLOR_NONSELECTED);
	}
	else
	{
		setFillColor(PI_BACKGROUND_NONSELECTED);
		setTextsFillColor(PI_TEXTCOLOR_NONSELECTED);
	}
}


void PlaylistItem::updateTextsPosiiton()
{
	if (m_songNameText && m_durationText)
	{
		sf::FloatRect songNameTextBounds = m_songNameText->getGlobalBounds();
		sf::FloatRect durationTextBounds = m_durationText->getGlobalBounds();

		auto s1 = m_songNameText->getString().toAnsiString();
		auto s2 = m_durationText->getString().toAnsiString();

		float newHeightForSongNameText = ((getSize().y / 2.0f) - (songNameTextBounds.height / 2.0f)) - songNameTextBounds.top;
		m_songNameText->setPosition(-songNameTextBounds.left, newHeightForSongNameText);

		float newWidthForDurationText = getSize().x - durationTextBounds.width - durationTextBounds.left;
		float newHeightForDurationText = ((getSize().y / 2.0f) - (durationTextBounds.height / 2.0f)) - durationTextBounds.top;
		m_durationText->setPosition(newWidthForDurationText, newHeightForDurationText);
	}
}



SelectionState PlaylistItem::getSelectionState() const
{
	return m_selectionState;
}


void PlaylistItem::setSelectionState(SelectionState state)
{
	m_selectionState = state;
}


Text* PlaylistItem::getSongNameText() const
{
	return m_songNameText;
}


Text* PlaylistItem::getDurationText() const
{
	return m_durationText;
}

