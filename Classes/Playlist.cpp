#include "Playlist.h"
#include "RectangleShape.h"
#include "Text.h"



Playlist::Playlist(const sf::Vector2f& size)
	: Menu(MenuOrientation::VERTICAL, true)
	, m_size(size)
	, m_scrollView(nullptr)
	, m_fileSystemUtils(nullptr)
{
	init();
	Scheduler::getInstance()->scheduleUpdate(this);
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
	m_backgroundRect->setFillColor(sf::Color(50, 50, 50));
	this->addChild(m_backgroundRect);

	// ScrollView
	m_scrollView = new sf::View(sf::FloatRect(getPosition().x, getPosition().y, m_size.x, m_size.y));
	m_scrollView->setViewport(sf::FloatRect(getPosition().x / WINDOW_WIDTH, getPosition().y / WINDOW_HEIGHT, m_size.x / WINDOW_WIDTH, m_size.y / WINDOW_HEIGHT));
}


void Playlist::onMousePressed(sf::Event e)
{
	if (m_backgroundRect->contains(sf::Vector2f((float)(e.mouseButton.x), (float)(e.mouseButton.y))))
	{
		Menu::onMousePressed(e);
	}
}


void Playlist::onMouseReleased(sf::Event e)
{
	if (m_backgroundRect->contains(sf::Vector2f((float)(e.mouseButton.x), (float)(e.mouseButton.y))))
	{
		Menu::onMouseReleased(e);
	}
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


void Playlist::openFromDirectory()
{
	if (m_fileSystemUtils->showFolderDialog())
	{
		// TODO: refactor the mechanism of filebrowser and folderbrowser
		std::string folder = m_fileSystemUtils->getFolderBrowser()->getFolder();
		FileSystemUtils::DirectoryEntryList entries = m_fileSystemUtils->getFilesWithinFolder(folder);

		for (auto entry : entries)
		{
			// example:
			// entry.basename();			// "C-BooL - Magic Symphony ft. Giang Pham (Official Video)"
			// entry.branch_path();			// "C:/Users/Sharagoth/Music"
			// entry.directory_string();	// "C:\\Users\\Sharagoth\\Music\\C-BooL - Magic Symphony ft. Giang Pham (Official Video).mp3"
			// entry.filename();			// "C-BooL - Magic Symphony ft. Giang Pham (Official Video).mp3"
			// entry.file_string();			// "C:\\Users\\Sharagoth\\Music\\C-BooL - Magic Symphony ft. Giang Pham (Official Video).mp3"
			
			std::string fullPath = entry.directory_string();
			std::string fileExt = fullPath.substr(fullPath.rfind('.') + 1);

			if (isSupportedFileExt(fileExt))
			{
				PlaylistItem* entity = createPlaylistItem(fullPath);
				this->addChild(entity);
			}
		}
	}
}


PlaylistItem* Playlist::createPlaylistItem(std::string& path)
{
	const float height = C2WW(30.0f);

	PlaylistItem* item = new PlaylistItem(path);
	item->setSize(sf::Vector2f(m_backgroundRect->getSize().x, height));

	return item;
}


void Playlist::clearPlaylist()
{
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


void Playlist::onUpdate(float dt)
{
	// update scroll view
	// ScrollView cannot be add as a child to anything

	const sf::Vector2f position = getPosition();
	
	m_scrollView->setCenter(position.x + m_size.x / 2, position.y + m_size.y / 2);
	m_scrollView->setSize(sf::Vector2f(m_size.x, m_size.y));

	m_scrollView->setViewport(sf::FloatRect(position.x / WINDOW_WIDTH, 
											position.y / WINDOW_HEIGHT,
											m_size.x / WINDOW_WIDTH,
											m_size.y / WINDOW_HEIGHT));
}


sf::View* Playlist::getScrollView() const
{
	return m_scrollView;
}


PlaylistItem* Playlist::getCurrentAudioFile() const
{
	return dynamic_cast<PlaylistItem*>(m_selectedItem);
}
