#ifndef MP3_H_INCLUDED
#define MP3_H_INCLUDED


#include <SFML/Audio.hpp>
#include "mpg123.h"


class Mp3 : public sf::SoundStream
{
public:

	Mp3();
	~Mp3();

	bool openFromFile(const std::string& filename);
	bool openFromMemory(void* data, size_t sizeInBytes);
	sf::Time getDuration() const;

	size_t  myRealBufferSize;
	short*  myRealBuffer;
	unsigned char*  myBuffer;

protected:

	bool onGetData(Chunk& data);
	void onSeek(sf::Time timeOffset);

private:

	sf::Time		myDuration;
	mpg123_handle*  myHandle;
	size_t          myBufferSize;
	sf::Mutex       myMutex;
};


#endif // MP3_H_INCLUDED