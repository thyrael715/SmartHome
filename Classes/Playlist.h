#pragma once

#include "RectangleShape.h"
#include "PlaylistItem.h"
#include "FileSystemUtils.h"


class Playlist : public RectangleShape
{
public:

	Playlist(const sf::Vector2f& size = sf::Vector2f(0.0f, 0.0f));
	virtual ~Playlist();

	sf::View* getScrollView() const;
	AudioFile* getCurrentAudioFile() const;
	
	void openFromFile();
	void openFromDirectory();

public:

	virtual void onUpdate(float dt) override;
	
private:
	
	void init();

	PlaylistItem* createPlaylistItem(std::string& path);
	void clearPlaylist();

	bool isSupportedFileExt(std::string& fileExt) const;

private:

	std::vector<PlaylistItem*> m_audioFiles;
	PlaylistItem* m_currentPlaylistItem;
	sf::Font* m_font;
	sf::View* m_scrollView;
	FileSystemUtils* m_fileSystemUtils;
};