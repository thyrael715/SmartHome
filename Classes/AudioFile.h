#pragma once

#include <SFML\System.hpp>

#define OUTPUTRATE 48000
#define SPECTRUMSIZE 4096 //Defines the accuracy of the analyzed spectrum

/// NOTE: if compiling FMOD gives you an error, try uncommenting the following line
//#define REDEFINE_FMOD_STDCALL

//FMOD include
#ifdef REDEFINE_FMOD_STDCALL
#define _stdcall __stdcall
#endif
#include <fmod.h>
#ifdef REDEFINE_FMOD_STDCALL
#undef _stdcall
#endif


class AudioFile
{

public:

	enum Status
	{
		Stopped,
		Paused,
		Playing
	};

	AudioFile(const char *song_name);
	~AudioFile();

	void play();
	void pause();
	void stop();

	void setVolume(float volume);
	float getVolume() const;
	sf::Time getDuration() const;
	std::string getName() const;
	Status getStatus() const;
	void getSpectrum(float* spectrumL, float* spectrumR) const;

	void update() const;
		
private:

	AudioFile(const AudioFile &obj); //Copy constructor
	AudioFile &operator=(const AudioFile &obj); //Assign operator

	void setIsPaused(bool pause);
	bool getIsPaused() const;

	void run();

	std::string getFileExtension() const;
	std::string getFileNameWithoutExt() const;

private:

	std::string m_songName;
	FMOD_SYSTEM *fmod_system;
	FMOD_SOUND *music;
	FMOD_CHANNEL *channel;
};