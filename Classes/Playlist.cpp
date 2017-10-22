#include "Playlist.h"
#include "RectangleShape.h"
#include "Text.h"



Playlist::Playlist(const sf::Vector2f& size)
	: RectangleShape(size)
	, m_currentPlaylistItem(nullptr)
	, m_font(nullptr)
	, m_scrollView(nullptr)
	, m_fileSystemUtils(nullptr)
{
	init();
	Scheduler::getInstance()->scheduleUpdate(this);
}


Playlist::~Playlist()
{
	SAFE_DELETE(m_font);
	SAFE_DELETE(m_currentPlaylistItem);
	SAFE_DELETE(m_fileSystemUtils);
}


void Playlist::init()
{
	m_fileSystemUtils = new FileSystemUtils();
	
	m_font = new sf::Font();

	if (!m_font->loadFromFile("Fonts\\arial.ttf"))
	{
		// error...
	}

	m_scrollView = new sf::View(sf::FloatRect(getPosition().x, getPosition().y, m_size.x, m_size.y));
	m_scrollView->setViewport(sf::FloatRect(getPosition().x / WINDOW_WIDTH, getPosition().y / WINDOW_HEIGHT, m_size.x / WINDOW_WIDTH, m_size.y / WINDOW_HEIGHT));
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
				m_audioFiles.push_back(entity);

				this->addChild(entity);
			}
		}
	}
}


PlaylistItem* Playlist::createPlaylistItem(std::string& path)
{
	PlaylistItem* item = new PlaylistItem(path);
	item->registerEvent(EventType::MOUSE);
	item->setSize(sf::Vector2f(this->getGlobalBounds().width, item->getSize().y));
	item->addEvent(EventType::MOUSE, [=]()
	{		
		if (item->getSelectionState() == SELECTIONSTATE_SELECTED)
		{
			std::cout << "\nCurrently playing: " << item->getDurationText()->getString().toAnsiString();

			if (m_currentPlaylistItem && m_currentPlaylistItem != item)
			{
				m_currentPlaylistItem->setSelectionState(SELECTIONSTATE_UNSELECTED);
				m_currentPlaylistItem->stop();
			}

			m_currentPlaylistItem = item;
			m_currentPlaylistItem->play();
		}
		else if (item->getSelectionState() == SELECTIONSTATE_PRESELECTED)
		{
			if (m_currentPlaylistItem)
			{
				m_currentPlaylistItem->setSelectionState(SELECTIONSTATE_UNSELECTED);
			}

			m_currentPlaylistItem = item;
		}
	});

	item->RectangleShape::setPosition(0, m_audioFiles.size() * item->getSize().y);
	
	//m_audioFiles.push_back(audio);

	this->addChild(item);

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
	const sf::Vector2f size = getSize();
	
	m_scrollView->setCenter(position.x + size.x / 2, position.y + size.y / 2);
	m_scrollView->setSize(sf::Vector2f(size.x, size.y));
	m_scrollView->setViewport(sf::FloatRect(position.x / WINDOW_WIDTH, position.y / WINDOW_HEIGHT, size.x / WINDOW_WIDTH, size.y / WINDOW_HEIGHT));
}


sf::View* Playlist::getScrollView() const
{
	return m_scrollView;
}


AudioFile* Playlist::getCurrentAudioFile() const
{
	return m_currentPlaylistItem;
}
