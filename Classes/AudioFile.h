#pragma once

#include <SFML\Audio.hpp>


/*
* Adapter class for different Audioformat
*/
class AudioFile
{

public:

	AudioFile(const std::string &filename);
	virtual ~AudioFile();

	// TODO: Refac this 
	// This is only because I want Audiofile to handle the different Soundstreams
	// Currently there are two different Soundstream: MP3 and not MP3 (MP3 is not supported by SFML)
	void play() { m_soundStream->play(); };
	void pause() { m_soundStream->pause(); };
	void stop() { m_soundStream->stop(); };

	unsigned int getChannelCount() const { return m_soundStream->getChannelCount(); };
	unsigned int getSampleRate() const { return m_soundStream->getSampleRate(); };
	sf::SoundSource::Status getStatus() const { return m_soundStream->getStatus(); };
	void setPlayingOffset(sf::Time timeOffset) { m_soundStream->setPlayingOffset(timeOffset); };
	sf::Time getPlayingOffset() const { return m_soundStream->getPlayingOffset(); };
	void setLoop(bool loop) { m_soundStream->setLoop(loop); };
	bool getLoop() const { return m_soundStream->getLoop(); };
	void setPitch(float pitch) { m_soundStream->setPitch(pitch); };
	void setVolume(float volume) { m_soundStream->setVolume(volume); };
	void setPosition(float x, float y, float z) { m_soundStream->setPosition(x, y, z); };
	void setPosition(const sf::Vector3f& position) { m_soundStream->setPosition(position); };
	void setRelativeToListener(bool relative) { m_soundStream->setRelativeToListener(relative); };
	void setMinDistance(float distance) { m_soundStream->setMinDistance(distance); };
	void setAttenuation(float attenuation) { m_soundStream->setAttenuation(attenuation); };
	float getPitch() const { return m_soundStream->getPitch(); };
	float getVolume() const { return m_soundStream->getVolume(); };
	sf::Vector3f getPosition() const { return m_soundStream->getPosition(); };
	bool isRelativeToListener() const { return m_soundStream->isRelativeToListener(); };
	float getMinDistance() const { return m_soundStream->getMinDistance(); };
	float getAttenuation() const { return m_soundStream->getAttenuation(); };
	sf::Time getDuration() const;

	std::string getFullPath() const;
	std::string getFileName() const;
		
private:

	std::string getFileExtension() const;
	std::string getFileNameWithoutExt() const;

private:

	sf::SoundStream* m_soundStream;

	std::string m_fileName;
	std::string m_fullPath;
};