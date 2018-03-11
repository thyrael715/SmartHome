#pragma once

#include "Object.h"
#include "Playlist.h"


class AudioPlayer : public Object
{
	enum ButtonType
	{
		UNKNOWN,
		START,
		PAUSE,
		STOP
	};
	
public:

	CREATE_FUNC(AudioPlayer);
	virtual ~AudioPlayer();

	void init();

	void play();
	void pause();
	void stop();

public:

	virtual void onUpdate(float dt) override;

protected:

	AudioPlayer();
	void run();

protected:

	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates& states) const override;
		
private:

	Playlist* m_playlist;
	sf::VertexArray VA2;
};