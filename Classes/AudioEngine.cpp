#include "AudioEngine.h"
#include "Defaults.h"


AudioEngine::AudioEngine()
{
	fmod_errorcheck(FMOD_System_Create(&fmod_system));
	fmod_errorcheck(FMOD_System_SetSoftwareFormat(fmod_system, OUTPUTRATE, FMOD_SOUND_FORMAT_PCM16, 2, 0, FMOD_DSP_RESAMPLER_LINEAR));
	fmod_errorcheck(FMOD_System_Init(fmod_system, 32, FMOD_INIT_NORMAL, 0));
}


AudioEngine::~AudioEngine()
{
	fmod_errorcheck(FMOD_System_Release(fmod_system));
}


AudioEngine& AudioEngine::getInstance()
{
	static AudioEngine ed;
	return ed;
}


FMOD_SYSTEM* AudioEngine::getSystem() const
{
	return fmod_system;
}


