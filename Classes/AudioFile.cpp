#include "AudioFile.h"
#include "Defaults.h"
#include "Mp3.h"


AudioFile::AudioFile(const std::string &filename)
	: m_fileName("")
	, m_fullPath(filename)
{	
	if (getFileExtension() == "mp3")
	{
		m_soundStream = new Mp3();
		static_cast<Mp3*>(m_soundStream)->openFromFile(filename);
	}
	else
	{
		m_soundStream = new sf::Music();
		static_cast<sf::Music*>(m_soundStream)->openFromFile(filename);
	}
	
	m_fileName = getFileNameWithoutExt();
}


AudioFile::~AudioFile()
{ 
	SAFE_DELETE(m_soundStream);
}


sf::Time AudioFile::getDuration() const
{
	if (getFileExtension() == "mp3")
	{
		return static_cast<Mp3*>(m_soundStream)->getDuration();
	}
	else
	{
		return static_cast<sf::Music*>(m_soundStream)->getDuration();
	}
}


std::string AudioFile::getFileExtension() const
{
	auto ext = m_fullPath.substr(m_fullPath.rfind(".") + 1);
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

	return ext;
}


std::string AudioFile::getFileNameWithoutExt() const
{
	// the result without +1 would be = "\\<audio file name>"
	size_t start = m_fullPath.rfind("\\") + 1;
	size_t end = (m_fullPath.rfind(".")) - start;

	std::string retVal = m_fullPath.substr(start, end);
	
	return retVal;
}


std::string AudioFile::getFullPath() const
{
	return m_fullPath;
}


std::string AudioFile::getFileName() const
{
	return m_fileName;
}