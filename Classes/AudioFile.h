#pragma once

#include <mpg123.h>
#include <SFML\Audio.hpp>
#include "Mp3.h"


//class AudioFile : public sf::Music
class AudioFile : public sfe::Mp3
{

public:

	AudioFile(const std::string &filename);
	virtual ~AudioFile();

	bool openFromFile(const std::string& filename);

	std::string getFileExtension() const;
	std::string getFileNameWithoutExt() const;

	std::string getFullName() const { return m_fullName; };
	std::string getTitle() const { return m_title; };
	std::string getArtist() const { return m_artist; };
	std::string getAlbum() const { return m_album; };
	unsigned short getYear() const { return m_year; };
	sf::Time getDuration() const { return m_duration; };

private:

	void initInternalData();
	
protected:

	std::string m_fileName;
	std::string m_fullName;
	std::string m_title;
	std::string m_artist;
	std::string m_album;
	unsigned short m_year;
	sf::Time m_duration;
};