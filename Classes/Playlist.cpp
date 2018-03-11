#include "Playlist.h"
#include "RectangleShape.h"
#include "Text.h"


#define PL_BUTTONS_HEIGHT 20


Playlist::Playlist(const sf::Vector2f& size)
	: m_size(size)
	, m_scrollMenu(nullptr)
	, m_fileSystemUtils(nullptr)
{
	init();
}


Playlist::~Playlist()
{
	SAFE_DELETE(m_fileSystemUtils);
}


void Playlist::init()
{
	// FileSystem
	m_fileSystemUtils = new FileSystemUtils();

	// Background
	m_backgroundRect = new RectangleShape(m_size);
	m_backgroundRect->setFillColor(sf::Color(255, 0, 0));
	m_backgroundRect->move(sf::Vector2f(0, (-1)*PL_BUTTONS_HEIGHT));
	this->addChild(m_backgroundRect);

	// Scrollable menu
	const sf::Vector2f border(2.0f, 2.0f);

	m_scrollMenu = new ScrollMenu(VERTICAL, true);
	m_scrollMenu->setSize(m_size - border);
	m_scrollMenu->setPosition(border.x / 2.0f, border.y / 2.0f);
	m_scrollMenu->setBackgroundColor(sf::Color(41, 41, 53));
	m_scrollMenu->move(sf::Vector2f(0, (-1)*PL_BUTTONS_HEIGHT));
	this->addChild(m_scrollMenu);
}


void Playlist::openFromFile()
{
	//if (m_fileSystemUtils->showFileDialog())
	//{
	//	// TODO: refactor the mechanism of filebrowser and folderbrowser
	//	std::vector<std::string> files = m_fileSystemUtils->getFileBrowser()->getFileNamesWithFolder();

	//	for (auto file : files)
	//	{
	//		AudioFile* audioFile = new AudioFile();
	//		audioFile->openFromFile(file.c_str());
	//		m_audioFiles.push_back(audioFile);
	//	}
	//}
}


// example:
// entry.basename();			// "C-BooL - Magic Symphony ft. Giang Pham (Official Video)"
// entry.branch_path();			// "C:/Users/Sharagoth/Music"
// entry.directory_string();	// "C:\\Users\\Sharagoth\\Music\\C-BooL - Magic Symphony ft. Giang Pham (Official Video).mp3"
// entry.filename();			// "C-BooL - Magic Symphony ft. Giang Pham (Official Video).mp3"
// entry.file_string();			// "C:\\Users\\Sharagoth\\Music\\C-BooL - Magic Symphony ft. Giang Pham (Official Video).mp3"

void Playlist::openFromDirectory()
{
	// TODO: make it threadsafe, GUI should NOT be stopped while browsing
	if (m_fileSystemUtils->showFolderDialog())
	{
		// TODO: refactor the mechanism of filebrowser and folderbrowser
		std::string folder = m_fileSystemUtils->getFolderBrowser()->getFolder();
		FileSystemUtils::DirectoryEntryList entries = m_fileSystemUtils->getFilesWithinFolder(folder);

		for (auto entry : entries)
		{
			std::string fullPath = entry.directory_string();
			std::string fileExt = fullPath.substr(fullPath.rfind('.') + 1);

			if (isSupportedFileExt(fileExt) && m_scrollMenu)
			{
				addPlaylistItem(fullPath);
			}
		}
	}
}


void Playlist::addPlaylistItem(std::string& path)
{
	const float height = C2WW(30.0f);

	PlaylistItem* entity = new PlaylistItem(path);
	entity->setSize(m_scrollMenu->getSizeWithoutScrollBar().x, height);

	m_scrollMenu->addChild(entity);
}


void Playlist::clearPlaylist()
{
	// Stop currently playing PlaylistItem
	if (PlaylistItem* actItem = getActivatedItem())
	{
		//actItem->stop();
	}

	// TODO: there is a problem somewhere
	for (auto it = m_children.cbegin(); it != m_children.cend(); ++it)
	{
		if (dynamic_cast<Text*>(*it) != nullptr)
		{
			delete *it;
			it = m_children.erase(it);
		}
	}
}


bool Playlist::isSupportedFileExt(std::string& fileExt) const
{
	const std::vector<std::string> supportedFileExts = {
		"mp3", "ogg", "wav", "flac", "aiff", "au", "raw", "paf", "svx", "nist", "voc", "ircam", "w64", "mat4", "mat5", "pvf", "htk", "sds", "avr", "sd2", "caf", "wve", "mpc2k", "rf64"
	};

	for (auto actExt : supportedFileExts)
	{
		if (actExt == fileExt)
		{
			return true;
		}
	}

	return false;
}


PlaylistItem* Playlist::getActivatedItem() const
{
	return dynamic_cast<PlaylistItem*>(m_scrollMenu->getActivatedItem());
}

PlaylistItem* Playlist::getSelectedItem() const
{
	return dynamic_cast<PlaylistItem*>(m_scrollMenu->getSelectedItem());
}
