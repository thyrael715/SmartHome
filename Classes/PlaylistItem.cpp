#include "PlaylistItem.h"


#define PI_TEXTCOLOR_SELECTED		sf::Color(0, 0, 0)
#define PI_TEXTCOLOR_NONSELECTED	sf::Color(255, 255, 255)
#define PI_BACKGROUND_SELECTED		sf::Color(30, 30, 30)
#define PI_BACKGROUND_NONSELECTED	sf::Color(10, 10, 10)
#define PI_BACKGROUND_ACTIVATED		sf::Color(40, 255, 255)

#define PI_TEXT_MARGIN		10
#define PI_TEXT_FONTSIZE	12


size_t PlaylistItem::m_instanceCounter = 0;


PlaylistItem::PlaylistItem(const sf::String& path)
	: AudioFile(path)
	, m_background(nullptr)
	, m_songNameText(nullptr)
	, m_durationText(nullptr)
	, m_font(nullptr)
	, m_size(0.0f, 0.0f)
{
	m_instanceCounter++;
	init();
}


PlaylistItem::~PlaylistItem()
{

}


void PlaylistItem::init()
{
	// TODO: create separate number Text for each entity

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

	std::string fullDurationStr = "  " + minutesInStr + ":" + secondsInStr;

	m_durationText = new Text(fullDurationStr.c_str(), *m_font);
	m_durationText->setFillColor(PI_TEXTCOLOR_NONSELECTED);
	this->addChild(m_durationText);

// #### Playlist item initialization #### 
	
	m_background = new RectangleShape();
	m_background->setFillColor(PI_BACKGROUND_NONSELECTED);
	this->addChild(m_background, 1);
	
// #### init volume ####

	this->setVolume(10.0f);
}


void PlaylistItem::initCallbacks()
{
	this->onActivate = [=](){
		setTextsFillColor(PI_TEXTCOLOR_SELECTED);
		m_background->setFillColor(PI_BACKGROUND_ACTIVATED);
		play();
	};

	this->onDeactivate = [=](){
		setTextsFillColor(PI_TEXTCOLOR_NONSELECTED);
		m_background->setFillColor(PI_BACKGROUND_NONSELECTED);
		stop();
	};

	this->onSelect = [=](){
		if (getStatus() != sf::SoundStream::Playing)
		{
			m_background->setFillColor(PI_BACKGROUND_SELECTED);
		}
	};

	this->onUnselect = [=](){
		if (getStatus() != sf::SoundStream::Playing)
		{
			m_background->setFillColor(PI_BACKGROUND_NONSELECTED);
		}
	};
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
		sf::FloatRect b1 = m_songNameText->getGlobalBounds();
		sf::FloatRect b2 = m_durationText->getGlobalBounds();

		float h1 = ((m_size.y / 2.0f) - (b1.height / 2.0f)) - b1.top;
		m_songNameText->setPosition(-b1.left + PI_TEXT_MARGIN, h1);

		float w2 = m_size.x - b2.width - b2.left;
		float h2 = ((m_size.y / 2.0f) - (b2.height / 2.0f)) - b2.top;
		m_durationText->setPosition(w2 - PI_TEXT_MARGIN, h2);

		// At last update songname text
		updateSongNameLength();
	}
}


void PlaylistItem::updateSongNameLength()
{
	if (m_songNameText && m_durationText)
	{
		Text tempText(m_fullName.c_str(), *m_font, m_songNameText->getCharacterSize());
		const auto maxSize = m_size.x - m_durationText->getGlobalBounds().width - (2 * PI_TEXT_MARGIN);

		if (tempText.getGlobalBounds().width > maxSize)
		{
			for (unsigned short j = tempText.getString().getSize(); j >= 0; --j)
			{
				std::string str = tempText.getString().toAnsiString().substr(0, j) + "...";
				tempText = Text(str.c_str(), *m_font, tempText.getCharacterSize());

				if (tempText.getGlobalBounds().width < maxSize)
				{
					m_songNameText->setString(str);
					break;
				}
			}
		}
		else
		{
			m_songNameText->setString(tempText.getString());
		}
	}
}

void PlaylistItem::setSize(const sf::Vector2f& size)
{
	m_size = size;

	if (m_background)
		m_background->setSize(m_size);

	updateTextsPosition();
}


sf::Vector2f PlaylistItem::getSize() const
{
	return m_size;
}


void PlaylistItem::setWidth(const float& width)
{
	m_size.x = width;
	this->setSize(m_size);
}


void PlaylistItem::setHeight(const float& height)
{
	m_size.y = height;
	this->setSize(m_size);
}