#pragma once


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
#include <iostream>

#ifdef REDEFINE_FMOD_STDCALL
#undef _stdcall
#endif


//Function for handling FMOD errors
inline void fmod_errorcheck(const FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
	}
}


class AudioEngine
{
public:

	static AudioEngine& getInstance();
	FMOD_SYSTEM* getSystem() const;

	~AudioEngine();

private:

	AudioEngine();

	AudioEngine(const AudioEngine& old) = delete;
	AudioEngine& operator=(const AudioEngine& old) = delete;

private:

	FMOD_SYSTEM *fmod_system;
};