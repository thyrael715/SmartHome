#include "AudioPlayer.h"
#include "ButtonArc.h"
#include "Text.h"



#define FPS 60.0 //Frames per second

#define MOTION_BLUR_AMOUNT 0.25f //Amount of "motion blur" in range from 0 to 1

//Defines the way the bars are drawn
//in type 1 multiple bars are combined into one or one bar is broken into multiple bars so that all the drawn parts have same width
//in type 2 all the existing bars are drawn with a variable width
#define BAR_TYPE 1

#define SMOOTH_SPEC //Does some smoothing to the spectrum itself
#define SMOOTH_BARS //Does some smoothing to the bars, does basically the same as SMOOTH_SPEC when BAR_TYPE is 2

#define VERTEX_ARRAY_SIZE 4



AudioPlayer::AudioPlayer()
	: m_playlist(nullptr)
{

}


AudioPlayer::~AudioPlayer()
{
	//SAFE_DELETE(m_playlist);
}


void AudioPlayer::init()
{
	// create playlist

	const float playList_W = C2WW(300.0f);
	const float playList_H = C2WH(300.0f);

	m_playlist = new Playlist(sf::Vector2f(playList_W, playList_H));
	m_playlist->setPosition(WINDOW_WIDTH - playList_W, WINDOW_HEIGHT - playList_H);

	// create buttons

	ButtonArc* btn = new ButtonArc(91.0f, 106.0f, 200.0f);
	btn->setThickness(35);
	btn->addEvent(EventType::MOUSE, [](){
		std::cout << "Haddaway has been selected\n";
	});
	this->addChild(btn);


	ButtonArc* btn5 = new ButtonArc(155.0f, 170.0f, 200.0f);
	btn5->setThickness(35);
	btn5->setFillColor(sf::Color::Red);
	btn5->addEvent(EventType::MOUSE, CALLBACK_0(Playlist::openFromDirectory, m_playlist));
	this->addChild(btn5);

	Scheduler::getInstance()->scheduleUpdate(this);
}


void AudioPlayer::play()
{
	m_playlist->getSelectedItem()->play();
}


void AudioPlayer::pause()
{
	m_playlist->getActivatedItem()->pause();
}


void AudioPlayer::stop()
{
	m_playlist->getActivatedItem()->stop();
}

void AudioPlayer::onDraw(sf::RenderTarget& target, sf::RenderStates& states) const
{
	if (m_playlist)
	{
		target.draw(*m_playlist);
		target.draw(VA2);
	}
}


void AudioPlayer::onUpdate(float dt)
{
	if (m_playlist->getActivatedItem())
	{
		run();
	}
}


void AudioPlayer::run()
{
	//Rather useless defines
#define SPECTRUMRANGE ((float)OUTPUTRATE / 2.0f) // 24000.0 Hz
#define BINSIZE (SPECTRUMRANGE / (float)SPECTRUMSIZE) // 5.8594 Hz

	//We do not show the full spectrum, instead just the interesting part
#define SPECTRUM_START 6 // 41.0156 Hz  (7 * BINSIZE)
#define SPECTRUM_END 2560 // 15000.0 Hz  (2560 * BINSIZE)

	//Storages for the left and right spectrums
	float spectrumL[SPECTRUMSIZE] = {0};
	float spectrumR[SPECTRUMSIZE] = {0};

	m_playlist->getActivatedItem()->getSpectrum(spectrumL, spectrumR);
	
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

		bar1_heights[i] = std::max((sumL + sumR) * 5.0, 0.0);
	}

	VA2.clear();
	VA2.setPrimitiveType(sf::TrianglesStrip);
	sf::Vector2f position(0, 800);
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

		sf::Vertex v1(position + sf::Vector2f(i * size, 0), sf::Color::White);
		sf::Vertex v2(position + sf::Vector2f(i * size, -height * (bar_amount - i)), sf::Color::White);
		sf::Vertex v3(position + sf::Vector2f(i * size + size, 0), sf::Color::White);
		sf::Vertex v4(position + sf::Vector2f(i * size + size, -height * (bar_amount - i)), sf::Color::White);

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