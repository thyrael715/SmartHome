#include "PlaylistItem.h"


#define PI_TEXTCOLOR_SELECTED		sf::Color(50, 50, 200)
#define PI_TEXTCOLOR_NONSELECTED	sf::Color(40, 255, 255, 255)
#define PI_BACKGROUND_SELECTED		sf::Color(255, 50, 50, 200)
#define PI_BACKGROUND_NONSELECTED	COLOR_TRANSPARENT

#define PI_TEXT_MARGIN		1
#define PI_TEXT_FONTSIZE	12


PlaylistItem::PlaylistItem(const sf::String& path)
	: AudioFile(path)
	, m_background(nullptr)
	, m_songNameText(nullptr)
	, m_durationText(nullptr)
	, m_font(nullptr)
	, m_size(0.0f, 0.0f)
{
	init();
}


PlaylistItem::~PlaylistItem()
{

}


void PlaylistItem::init()
{
	initCallbacks();

// #### init font ####

	m_font = new sf::Font();

	if (!m_font || !m_font->loadFromFile("Fonts\\arial.ttf"))
	{
		// error...
		return;
	}
	
// #### Title text initialization ####
	 
	m_songNameText = new Text(m_fullName.c_str(), *m_font, PI_TEXT_FONTSIZE);
	m_songNameText->setFillColor(PI_TEXTCOLOR_NONSELECTED);
	this->addChild(m_songNameText);

// #### Song duration text initialization ####

	const float songDurationInSec = m_duration.asSeconds();

	std::string minutesInStr = ITOS((int)(songDurationInSec) / 60);
	std::string secondsInStr = ITOS((int)(songDurationInSec) % 60);

	// if seconds are in range of [1..9] then a '0' has to be inserted. ie.: 6:5 -> 6:05
	if (secondsInStr.size() == 1)
	{
		secondsInStr = "0" + secondsInStr;
	}

	std::string space = "  ";
	std::string fullDurationStr = space + minutesInStr + ":" + secondsInStr;

	m_durationText = new Text(fullDurationStr.c_str(), *m_font);
	m_durationText->setFillColor(PI_TEXTCOLOR_NONSELECTED);
	this->addChild(m_durationText);

// #### Playlist item initialization #### 
	
	const float heightScaler = 1.5f;

	sf::FloatRect songNameTextBounds = m_songNameText->getGlobalBounds();
	sf::FloatRect durationTextBounds = m_durationText->getGlobalBounds();

	m_background = new RectangleShape(sf::Vector2f(songNameTextBounds.width + durationTextBounds.width, heightScaler * PI_TEXT_FONTSIZE));
	m_background->setFillColor(PI_BACKGROUND_NONSELECTED);
	this->addChild(m_background);
	
// #### init volume ####

	this->setSize(m_background->getSize());
	this->setVolume(10.0f);
}


void PlaylistItem::initCallbacks()
{
	this->onActivate = [=](){
		setTextsFillColor(PI_TEXTCOLOR_SELECTED);
		play();
	};
	this->onDeactivate = [=](){
		setTextsFillColor(PI_TEXTCOLOR_NONSELECTED);
		stop();
	};
	this->onSelect = [=](){
		if (m_background)
		{
			m_background->setFillColor(PI_BACKGROUND_SELECTED);
		}
	};
	this->onUnselect = [=](){
		if (m_background)
		{
			m_background->setFillColor(PI_BACKGROUND_NONSELECTED);
		}
	};
}


void PlaylistItem::setSize(const sf::Vector2f& size)
{
	m_size = size;

	if (m_background)
		m_background->setSize(size);

	updateTextsPosition();
	updateSongNameLength();
}


sf::Vector2f PlaylistItem::getSize() const
{
	return m_size;
}


void PlaylistItem::setTextsFillColor(sf::Color color)
{
	if (m_songNameText && m_durationText)
	{
		m_songNameText->setFillColor(color);
		m_durationText->setFillColor(color);
	}
}


void PlaylistItem::updateTextsPosition()
{
	if (m_songNameText && m_durationText)
	{
		sf::FloatRect songNameTextBounds = m_songNameText->getGlobalBounds();
		sf::FloatRect durationTextBounds = m_durationText->getGlobalBounds();

		auto s1 = m_songNameText->getString().toAnsiString();
		auto s2 = m_durationText->getString().toAnsiString();

		float newHeightForSongNameText = ((m_size.y / 2.0f) - (songNameTextBounds.height / 2.0f)) - songNameTextBounds.top;
		m_songNameText->setPosition(-songNameTextBounds.left, newHeightForSongNameText);

		float newWidthForDurationText = m_size.x - durationTextBounds.width - durationTextBounds.left;
		float newHeightForDurationText = ((m_size.y / 2.0f) - (durationTextBounds.height / 2.0f)) - durationTextBounds.top;
		m_durationText->setPosition(newWidthForDurationText, newHeightForDurationText);
	}
}


void PlaylistItem::updateSongNameLength()
{
	if (m_songNameText && m_durationText)
	{
		const auto maxSize = m_size.x - m_durationText->getGlobalBounds().width;

		if (m_songNameText->getGlobalBounds().width > maxSize)
		{
			const float precent = m_size.x / m_songNameText->getGlobalBounds().width;
			const unsigned short maxCharLength = precent * m_fullName.length();

			for (unsigned short j = maxCharLength; j >= 0; --j)
			{
				std::string str = m_fullName.substr(0, j) + "...";
				Text tempText(str.c_str(), *m_font, m_songNameText->getCharacterSize());

				if (tempText.getGlobalBounds().width < maxSize)
				{
					m_songNameText->setString(str);
					break;
				}
			}
		}
	}
}


Text* PlaylistItem::getSongNameText() const
{
	return m_songNameText;
}


Text* PlaylistItem::getDurationText() const
{
	return m_durationText;
}

