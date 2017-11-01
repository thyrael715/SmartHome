#pragma once

#include "RectangleShape.h"
#include "PlaylistItem.h"
#include "FileSystemUtils.h"
#include "Menu.h"


class Playlist : public Menu
{
public:

	Playlist(const sf::Vector2f& size = sf::Vector2f(0.0f, 0.0f));
	virtual ~Playlist();

	sf::View* getScrollView() const;
	PlaylistItem* getCurrentAudioFile() const;
	
	void openFromFile();
	void openFromDirectory();

public:

	virtual void onMousePressed(sf::Event e) override;
	virtual void onMouseReleased(sf::Event e) override;
	virtual void onUpdate(float dt) override;
	
private:
	
	void init();

	PlaylistItem* createPlaylistItem(std::string& path);
	void clearPlaylist();

	bool isSupportedFileExt(std::string& fileExt) const;

private:

	RectangleShape* m_backgroundRect;
	sf::View* m_scrollView;
	FileSystemUtils* m_fileSystemUtils;
	sf::Vector2f m_size;
};