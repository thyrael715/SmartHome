#pragma once

#include "Object.h"
#include "AudioFile.h"
#include "FileSystemUtils.h"
#include "RectangleShape.h"


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

	void openFromFile();
	void openFromDirectory();
	void clearAllFiles();

	void play();
	void pause();
	void stop();

protected:

	AudioPlayer();

protected:

	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates& states) const override;
	virtual void onUpdate(float dt) override;

private:

	void createPlayList();

private:

	std::vector<AudioFile*> m_audioFiles;
	AudioFile* m_actAudioFile;
	FileSystemUtils* m_fileSystemUtils;
	sf::View* m_scrollView;
	sf::Font* m_font;
	RectangleShape* m_playList;
};