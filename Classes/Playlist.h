#pragma once

#include "ScrollMenu.h"
#include "PlaylistItem.h"
#include "FileSystemUtils.h"


class Playlist : public Object
{
public:

	Playlist(const sf::Vector2f& size = ZERO);
	virtual ~Playlist();

	sf::View* getScrollView() const;
	PlaylistItem* getActivatedItem() const;
	PlaylistItem* getSelectedItem() const;
	
	void openFromFile();
	void openFromDirectory();

private:
	
	void init();

	void addPlaylistItem(std::string& path);
	void clearPlaylist();
	bool isSupportedFileExt(std::string& fileExt) const;

private:

	RectangleShape* m_backgroundRect;
	ScrollMenu* m_scrollMenu;
	FileSystemUtils* m_fileSystemUtils;
	sf::Vector2f m_size;
};