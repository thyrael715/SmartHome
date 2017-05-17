#pragma once

#include <mpg123.h>
#include <SFML\Audio.hpp>
#include "Mp3.h"


//class AudioFile : public sf::Music
class AudioFile : public sfe::Mp3
{
public:

	struct InternalData
	{
		std::string title;
		std::string artist;
		std::string album;
		int year;
		sf::Time duration;
	};

public:

	AudioFile();
	virtual ~AudioFile();

	bool openFromFile(const std::string &filename);

	std::string getFileExtension() const;

	std::string getFullFileName() const;
	std::string getFileNameWithExt() const;
	std::string getFileNameWithoutExt() const;

	InternalData getInternalData() const;

private:

	void initInternalData();
	
	std::string m_fileName;
	InternalData m_internalData;
};