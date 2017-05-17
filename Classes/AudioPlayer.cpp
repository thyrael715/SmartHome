#include "AudioPlayer.h"
#include "ButtonArc.h"
#include "Text.h"


AudioPlayer::AudioPlayer()
	: m_fileSystemUtils(nullptr)
	, m_actAudioFile(nullptr)
	, m_playList(nullptr)
	, m_font(nullptr)
{

}


AudioPlayer::~AudioPlayer()
{
	SAFE_DELETE_CONTAINER(m_audioFiles);
	SAFE_DELETE(m_fileSystemUtils);
}


void AudioPlayer::init()
{
	m_fileSystemUtils = new FileSystemUtils();

	// create playlist

	this->createPlayList();
	
	// create buttons
	ButtonArc* btn = new ButtonArc(91.0f, 106.0f, 200.0f);
	btn->setThickness(35);
	btn->addEvent(EventType::MOUSE, CALLBACK_0(AudioPlayer::openFromFile, this));
	this->addChild(btn);

	ButtonArc* btn2 = new ButtonArc(107.0f, 122.0f, 200.0f);
	btn2->setThickness(35);
	btn2->addEvent(EventType::MOUSE, CALLBACK_0(AudioPlayer::openFromDirectory, this));
	this->addChild(btn2);

	ButtonArc* btn3 = new ButtonArc(123.0f, 138.0f, 200.0f);
	btn3->setThickness(35);
	btn3->addEvent(EventType::MOUSE, CALLBACK_0(AudioPlayer::play, this));
	this->addChild(btn3);

	ButtonArc* btn4 = new ButtonArc(139.0f, 154.0f, 200.0f);
	btn4->setThickness(35);
	btn4->addEvent(EventType::MOUSE, CALLBACK_0(AudioPlayer::pause, this));
	this->addChild(btn4);

	ButtonArc* btn5 = new ButtonArc(155.0f, 170.0f, 200.0f);
	btn5->setThickness(35);
	btn5->addEvent(EventType::MOUSE, CALLBACK_0(AudioPlayer::stop, this));
	this->addChild(btn5);
}


void AudioPlayer::createPlayList()
{
	const float playList_W = C2WW(300.0f);
	const float playList_H = C2WH(150.0f);
	const float margin = C2WH(10.0f);

	const float playList_X = (WINDOW_WIDTH / 2) - (playList_W / 2);
	const float playList_Y = WINDOW_HEIGHT - playList_H - playList_H;

	// Load it from a file
	m_font = new sf::Font();

	if (!m_font->loadFromFile("Fonts\\arial.ttf"))
	{
		// error...
		std::cout << "asd\n";
	}
	
	sf::Color bgColor(sf::Color(20, 20, 20, 255));
	sf::Color borderColor(sf::Color(0, 0, 0));

	m_playList = new RectangleShape(sf::Vector2f(playList_W, 1300.0f));
	m_playList->setPosition(playList_X, playList_Y);
	m_playList->setFillColor(bgColor);

	Text *text = new Text("Haddaway - What is Love", *m_font, 20);
	m_playList->addChild(text);
	


	m_scrollView = new sf::View(sf::FloatRect(playList_X, playList_Y, playList_W, playList_H));
	m_scrollView->setViewport(sf::FloatRect(playList_X / WINDOW_WIDTH, playList_Y / WINDOW_HEIGHT, playList_W / WINDOW_WIDTH, playList_H / WINDOW_HEIGHT));



	//const float w = C2WW(300.0f);
	//const float h = C2WW(150.0f);

	//m_playList = new RectangleShape(sf::Vector2f(600.0f, 1300.0f));
	////m_playList->setPosition(0.0f, 100.0f);
	//m_playList->setFillColor(sf::Color::Red);


	//m_scrollView = new sf::View(sf::FloatRect(m_playList->getPosition().x, m_playList->getPosition().y, w, h));
	//m_scrollView->setViewport(sf::FloatRect(m_playList->getPosition().x / WINDOW_WIDTH, m_playList->getPosition().y / WINDOW_HEIGHT, w / WINDOW_WIDTH, h / WINDOW_HEIGHT));
}


void AudioPlayer::openFromFile()
{
	if (m_fileSystemUtils->showFileDialog())
	{
		std::vector<std::string> files = m_fileSystemUtils->getFileBrowser()->getFileNamesWithFolder();

		for (auto file : files)
		{
			AudioFile* audioFile = new AudioFile();
			audioFile->openFromFile(file.c_str());
			m_audioFiles.push_back(audioFile);
		}
	}
}


void AudioPlayer::openFromDirectory()
{
	if (m_fileSystemUtils->showFolderDialog())
	{
		std::string folder = m_fileSystemUtils->getFolderBrowser()->getFolder();
		FileSystemUtils::DirectoryEntryList entries = m_fileSystemUtils->getFilesWithinFolder(folder);

		for (auto entry : entries)
		{
			AudioFile* audioFile = new AudioFile();
			audioFile->openFromFile(entry.filename() + "/" + entry.filename());
			m_audioFiles.push_back(audioFile);
		}
	}
}


void AudioPlayer::clearAllFiles()
{
	SAFE_DELETE_CONTAINER(m_audioFiles);
}


void AudioPlayer::play()
{
	m_actAudioFile->play();
}


void AudioPlayer::pause()
{
	m_actAudioFile->setPlayingOffset(sf::seconds(100));
	//m_audioFiles[0]->pause();
}


void AudioPlayer::stop()
{
	m_actAudioFile->stop();
}


void AudioPlayer::onDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	target.setView(*m_scrollView);

	target.draw(*m_playList);

	//sf::RectangleShape r(sf::Vector2f(800, 1450));
	//r.setFillColor(sf::Color::Red);

	//target.draw(r);

	//sf::CircleShape c(100);
	//c.setPosition(100, 0);
	//target.draw(c);

	//target.setView(Defaults::getInstance()->getMainView());
}


void AudioPlayer::onUpdate(float dt)
{

}