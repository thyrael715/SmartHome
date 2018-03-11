#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <algorithm>

#define OUTPUTRATE 48000
#define SPECTRUMSIZE 4096 //Defines the accuracy of the analyzed spectrum

/// NOTE: if compiling FMOD gives you an error, try uncommenting the following line
//#define REDEFINE_FMOD_STDCALL

//FMOD include
#ifdef REDEFINE_FMOD_STDCALL
#define _stdcall __stdcall
#endif
#include <fmod.h>
#include <fmod_errors.h>
#ifdef REDEFINE_FMOD_STDCALL
#undef _stdcall
#endif


//Function for handling FMOD errors
inline void fmod_errorcheck(const FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
	}
}


/*
The class for initializing FMOD and playing and analyzing music
*/
class sound_system_c {
private:
	sound_system_c(const sound_system_c &obj); //Copy constructor
	sound_system_c &operator=(const sound_system_c &obj); //Assign operator

	FMOD_SYSTEM *fmod_system;
	FMOD_SOUND *music;
	FMOD_CHANNEL *channel;
		
public:
	sound_system_c(FMOD_SYSTEM* system_pointer, const char *song_name);
	~sound_system_c();
	std::string getName() const;
	void play_music();

	void pause(){
		setIsPaused(!getIsPaused());
	}
	void stop(){ fmod_errorcheck(FMOD_Channel_Stop(channel)); };

	void setVolume(float volume);
	void setIsPaused(bool pause);
	bool getIsPaused() const;
	unsigned int getDuration();
	void get_spectrum(float *spectrumL, float *spectrumR) const;
	void update() const;
	void run();

	std::string m_songName;
	sf::VertexArray VA2;
};