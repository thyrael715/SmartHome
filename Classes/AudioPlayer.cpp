#include "AudioPlayer.h"
#include "ButtonArc.h"
#include "Text.h"


AudioPlayer::AudioPlayer()
	: m_playlist(nullptr)
{

}


AudioPlayer::~AudioPlayer()
{
	//SAFE_DELETE(m_playlist);
}


void AudioPlayer::init()
{
	// create playlist

	const float playList_W = C2WW(300.0f);
	const float playList_H = C2WH(300.0f);

	m_playlist = new Playlist(sf::Vector2f(playList_W, playList_H));
	m_playlist->setPosition(WINDOW_WIDTH - playList_W, WINDOW_HEIGHT - playList_H);

	// create buttons

	ButtonArc* btn = new ButtonArc(91.0f, 106.0f, 200.0f);
	btn->setThickness(35);
	btn->addEvent(EventType::MOUSE, [](){
		std::cout << "Haddaway has been selected\n";
	});
	this->addChild(btn);


	ButtonArc* btn5 = new ButtonArc(155.0f, 170.0f, 200.0f);
	btn5->setThickness(35);
	btn5->setFillColor(sf::Color::Red);
	btn5->addEvent(EventType::MOUSE, CALLBACK_0(Playlist::openFromDirectory, m_playlist));
	this->addChild(btn5);
}


void AudioPlayer::play()
{
	m_playlist->getCurrentAudioFile()->play();
}


void AudioPlayer::pause()
{
	m_playlist->getCurrentAudioFile()->pause();
}


void AudioPlayer::stop()
{
	m_playlist->getCurrentAudioFile()->stop();
}

void AudioPlayer::onDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	if (m_playlist)
	{
		target.draw(*m_playlist);
	}
}