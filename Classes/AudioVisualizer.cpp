
#define FPS 60.0 //Frames per second

#define MOTION_BLUR_AMOUNT 0.25f //Amount of "motion blur" in range from 0 to 1

//Defines the way the bars are drawn
//in type 1 multiple bars are combined into one or one bar is broken into multiple bars so that all the drawn parts have same width
//in type 2 all the existing bars are drawn with a variable width
#define BAR_TYPE 1

#define SMOOTH_SPEC //Does some smoothing to the spectrum itself
#define SMOOTH_BARS //Does some smoothing to the bars, does basically the same as SMOOTH_SPEC when BAR_TYPE is 2

#define VERTEX_ARRAY_SIZE 4



/** sound_system.cpp **/
#include "AudioVisualizer.h"

using namespace sf;


sound_system_c::sound_system_c(FMOD_SYSTEM* system_pointer, const char *song_name) {

	fmod_system = system_pointer;
	m_songName = song_name;

	// Init FMOD
	//fmod_errorcheck(FMOD_System_Create(&fmod_system));
	//fmod_errorcheck(FMOD_System_SetSoftwareFormat(fmod_system, OUTPUTRATE, FMOD_SOUND_FORMAT_PCM16, 2, 0, FMOD_DSP_RESAMPLER_LINEAR));
	//fmod_errorcheck(FMOD_System_Init(fmod_system, 32, FMOD_INIT_NORMAL, 0));
	// Init song
	fmod_errorcheck(FMOD_System_CreateStream(fmod_system, song_name, FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE | FMOD_UNIQUE, 0, &music));
}

sound_system_c::~sound_system_c() {
	fmod_errorcheck(FMOD_Sound_Release(music));
	fmod_errorcheck(FMOD_System_Close(fmod_system));
	fmod_errorcheck(FMOD_System_Release(fmod_system));
}

// paused attribute:
//		- false -> audio is being played
//		- true  -> audio is being paused
void sound_system_c::play_music() {
	fmod_errorcheck(FMOD_System_PlaySound(fmod_system, FMOD_CHANNEL_FREE, music, true, &channel));
}

//This analyzes the spectrum of the music FMODs own features
void sound_system_c::get_spectrum(float *spectrumL, float *spectrumR) const {
	fmod_errorcheck(FMOD_Channel_GetSpectrum(channel, spectrumL, SPECTRUMSIZE, 0, FMOD_DSP_FFT_WINDOW_TRIANGLE));
	fmod_errorcheck(FMOD_Channel_GetSpectrum(channel, spectrumR, SPECTRUMSIZE, 1, FMOD_DSP_FFT_WINDOW_TRIANGLE));
}

void sound_system_c::setVolume(float volume){
	fmod_errorcheck(FMOD_Channel_SetVolume(channel, volume));
}

void sound_system_c::setIsPaused(bool pause){
	fmod_errorcheck(FMOD_Channel_SetPaused(channel, pause));
}

bool sound_system_c::getIsPaused() const
{
	FMOD_BOOL isPaused = 0;
	fmod_errorcheck(FMOD_Channel_GetPaused(channel, &isPaused));

	return static_cast<bool>(isPaused);
}

unsigned int sound_system_c::getDuration(){
	unsigned int duration = 0;
	FMOD_Sound_GetLength(music, &duration, FMOD_TIMEUNIT_MS);

	return duration;
}

std::string sound_system_c::getName() const
{
	// the result without +1 would be = "\\<audio file name>"
	size_t start = m_songName.rfind("\\") + 1;
	size_t end = (m_songName.rfind(".")) - start;

	std::string retVal = m_songName.substr(start, end);

	return retVal;
}

void sound_system_c::update() const {
	fmod_errorcheck(FMOD_System_Update(fmod_system));
}

void sound_system_c::run()
{
	//Rather useless defines
	#define SPECTRUMRANGE ((float)OUTPUTRATE / 2.0f) // 24000.0 Hz
	#define BINSIZE (SPECTRUMRANGE / (float)SPECTRUMSIZE) // 5.8594 Hz

	//We do not show the full spectrum, instead just the interesting part
	#define SPECTRUM_START 6 // 41.0156 Hz  (7 * BINSIZE)
	#define SPECTRUM_END 2560 // 15000.0 Hz  (2560 * BINSIZE)

	//Storages for the left and right spectrums
	float spectrumL[SPECTRUMSIZE];
	float spectrumR[SPECTRUMSIZE];


	//Bars 1 have constant width
	//This figures out how to combine or divide the bars on the linear scale
	//  so that they use logarithmic scale instead
#if BAR_TYPE == 1
#define BAR_MULT 1.022 //Affects the amount of bars
	int bar_amount = 0; //The amount of bars
	float i = BAR_MULT - 1;
	float start = 0;
	while (start + i <= SPECTRUMSIZE - 1) {
		if (start >= SPECTRUM_START && start + i <= SPECTRUM_END) bar_amount++;
		start += i;
		i *= BAR_MULT;
	}

	int *bar_start = new int[bar_amount]; //Start of full frequencies
	int *bar_end = new int[bar_amount]; //End of full frequencies
	int *bar_first = new int[bar_amount]; //First non-full frequency
	float *bar_first_mult = new float[bar_amount]; //Mult for first non-full frequency
	int *bar_last = new int[bar_amount]; //Last non-full frequency
	float *bar_last_mult = new float[bar_amount]; //Mult for last non-full frequency

	i = BAR_MULT - 1;
	start = 0;
	while (start < SPECTRUM_START) { //Skip some frequencies
		start += i;
		i *= BAR_MULT;
	}
	for (int j = 0; j < bar_amount; j++) {
		const float end = start + i;
		bar_start[j] = ceil(start);
		bar_end[j] = floor(end);
		bar_first[j] = floor(start);
		bar_first_mult[j] = bar_start[j] == bar_first[j] ? 0.0 : 1.0 - start + floor(start);
		bar_last[j] = floor(end);
		bar_last_mult[j] = end - floor(end);
		if (bar_first[j] == bar_last[j]) {
			bar_first_mult[j] = end - start;
			bar_last_mult[j] = 0.0;
		}
		start += i;
		i *= BAR_MULT;
	}
#endif


	get_spectrum(spectrumL, spectrumR);
	float bass_sum = 0;
	float left_sum = 0;
	float right_sum = 0;
	float sound_sum = 0;

	//Smooth the actual spectrum
#ifdef SMOOTH_SPEC
	float temp_spectrumL[SPECTRUMSIZE];
	float temp_spectrumR[SPECTRUMSIZE];
	memcpy(temp_spectrumL, spectrumL, sizeof(float) * SPECTRUMSIZE);
	memcpy(temp_spectrumR, spectrumR, sizeof(float) * SPECTRUMSIZE);
	for (int i = SPECTRUM_START; i < SPECTRUM_END; i++) {
		spectrumL[i]
			= 0.1 * (temp_spectrumL[i - 2] + temp_spectrumL[i + 2])
			+ 0.2 * (temp_spectrumL[i - 1] + temp_spectrumL[i + 1])
			+ 0.4 * temp_spectrumL[i];
		spectrumR[i]
			= 0.1 * (temp_spectrumR[i - 2] + temp_spectrumR[i + 2])
			+ 0.2 * (temp_spectrumR[i - 1] + temp_spectrumR[i + 1])
			+ 0.4 * temp_spectrumR[i];
	}
#endif



#if BAR_TYPE == 1 //Bars with constant width
	float *bar1_heights = new float[bar_amount];
	//Calculate the heights for the bars
	for (int i = 0; i < bar_amount; i++) {
		float sumL = spectrumL[bar_first[i]] * bar_first_mult[i] + spectrumL[bar_last[i]] * bar_last_mult[i];
		float sumR = spectrumR[bar_first[i]] * bar_first_mult[i] + spectrumR[bar_last[i]] * bar_last_mult[i];

		for (int j = bar_start[i]; j < bar_last[i]; j++) {
			sumL += spectrumL[j - 1];
			sumR += spectrumR[j - 1];
		}

		bar1_heights[i] = std::max((sumL + sumR) * 5.0 - 0.04, 0.0) + 0.015;
	}

	VA2.clear();
	VA2.setPrimitiveType(TrianglesStrip);
	Vector2f position(0, 800);
	short size = 3;

	//Draw the bars
	for (int i = 0; i < bar_amount; i++) {
		const float x = -1.0 + (float)i / (float)bar_amount * 2.0;
		const float x2 = -1.0 + float(i + 1) / (float)bar_amount * 2.0;

		//Smooth the bars here
#ifdef SMOOTH_BARS
		const float height
			= 0.038 * (bar1_heights[std::max(i - 2, 0)] + bar1_heights[std::min(i + 2, bar_amount - 1)])
			+ 0.154 * (bar1_heights[std::max(i - 1, 0)] + bar1_heights[std::min(i + 1, bar_amount - 1)])
			+ 0.615 * bar1_heights[i];
#else
		const float height = bar1_heights[i];
#endif

		//Here we actually draw
		const float vertices[VERTEX_ARRAY_SIZE * 2] = {
			x, -1.0f,
			x, -1.0f + height,
			x2, -1.0f,
			x2, -1.0f + height };

		Vertex v1(position + sf::Vector2f(i * size, 0), Color::White);
		Vertex v2(position + sf::Vector2f(i * size, -height * (bar_amount - i)), Color::White);
		Vertex v3(position + sf::Vector2f(i * size + size, 0), Color::White);
		Vertex v4(position + sf::Vector2f(i * size + size, -height * (bar_amount - i)), Color::White);

		VA2.append(v1);
		VA2.append(v2);
		VA2.append(v3);
		VA2.append(v4);
	}
	delete[] bar1_heights;
#endif


#if BAR_TYPE == 1
	delete[] bar_start;
	delete[] bar_end;
	delete[] bar_first;
	delete[] bar_first_mult;
	delete[] bar_last;
	delete[] bar_last_mult;
#endif
}