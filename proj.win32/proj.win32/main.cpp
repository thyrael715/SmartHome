#include <iostream>
#include "Application.h"
#include "FileSystemUtils.h"


int main()
{
	Application* app = Application::create();
	app->run();

	delete app;

	return EXIT_SUCCESS;
}





//
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include "AudioVisualizer.h"
//#include <iostream>
//
//using namespace std;
//using namespace sf;
//
//
//
//void print(sound_system_c& s)
//{
//	size_t dur = s.getDuration();
//	std::cout << "\nDuration = " << dur;
//	std::cout << "\nMinute: " << ((dur / 1000) / 60) << ", seconds: " << ((dur / 1000) % 60);
//
//	auto name = s.getName();
//	std::cout << "\nname = " << name;
//}
//
//int main()
//{
//	RenderWindow window(VideoMode(900, 900, 32), "Window");
//
//	std::string filename = "C-BooL - Magic Symphony ft. Giang Pham (Official Video).mp3";
//	std::string filename2 = "Sonic Palms - On the Beach (Club Mix).mp3";
//	std::string filename3 = "Dion and The Belmonts - Greatest Hits - 13. Donna The Prima Donna.flac";
//	std::string filename4 = "Bangbros_-_Highflyer_Groove-T_Edit_(mp3.pm).mp3";
//	std::string filename5 = "C:\\Users\\Sharagoth\\Music\\Johnny Tillotson - Poetry In Motion.mp3";
//	std::string filename6 = "C:\\Users\\Sharagoth\\Music\\Bon Jovi - Its My Life (TuneSquad Bootleg).mp3";
//	std::string filename7 = "C:\\Users\\Sharagoth\\Music\\Civil War-Bay Of Pigs myhitmp3.top .mp3";
//	std::string filename8 = "C:\\Users\\Sharagoth\\Music\\Deep Spirit - Youre Makin Me High _Ozi Club Mix_.mp3";
//	std::string filename9 = "C:\\Users\\Sharagoth\\Music\\Dion_-_Runaround_Sue_HD[ListenVid.com].mp3";
//	std::string filename10 = "C:\\Users\\Sharagoth\\Music\\GLORYHAMMER - Rise Of The Chaos WizardsNapalm Records.mp3";
//	std::string filename11 = "C:\\Users\\Sharagoth\\Music\\Little Peggy March - I Will Follow Him (1963) HQ.mp3";
//	std::string filename12 = "C:\\Users\\Sharagoth\\Music\\Metalwings-Crying of the Sun myhitmp3.top.mp3";
//	std::string filename13 = "C:\\Users\\Sharagoth\\Music\\Orden_Ogan_-_Finis_Coronat_Opus_(mp3.pm).mp3";
//	std::string filename14 = "C:\\Users\\Sharagoth\\Music\\Peggy March - I Will Follow Him (50th Anniversary Recording).mp3";
//	std::string filename15 = "C:\\Users\\Sharagoth\\Music\\Samantha_Jade_-_Firestarter_(www.primemusic.ru).mp3";
//	std::string filename16 = "C:\\Users\\Sharagoth\\Music\\Dion and The Belmonts - Greatest Hits - 03. Runaround Sue.flac";
//	std::string filename17 = "C:\\Users\\Sharagoth\\Music\\Dion and The Belmonts - Greatest Hits - 13. Donna The Prima Donna.flac";
//	std::string filename18 = "C:\\Users\\Sharagoth\\Music\\01-imprezive_meets_pink_planet_-_alive_(original_mix)-zzzz.mp3";
//	std::string filename19 = "C:\\Users\\Sharagoth\\Music\\03. Army Of The Night.mp3";
//	std::string filename20 = "C:\\Users\\Sharagoth\\Music\\07 - Who Needs You.mp3";
//	std::string filename21 = "C:\\Users\\Sharagoth\\Music\\Another Furry Rave - In The UK [HD].mp3";
//
//
//	Event event;
//
//	FMOD_SYSTEM *fmod_system;
//	FMOD_RESULT result1 = FMOD_System_Create(&fmod_system);
//	FMOD_RESULT result2 = FMOD_System_SetSoftwareFormat(fmod_system, OUTPUTRATE, FMOD_SOUND_FORMAT_PCM16, 2, 0, FMOD_DSP_RESAMPLER_LINEAR);
//	FMOD_RESULT result3 = FMOD_System_Init(fmod_system, 32, FMOD_INIT_NORMAL, 0);
//
//	sound_system_c s1(fmod_system, filename.c_str()); print(s1);
//	sound_system_c s2(fmod_system, filename2.c_str()); print(s2);
//	sound_system_c s3(fmod_system, filename3.c_str()); print(s3);
//	sound_system_c s4(fmod_system, filename4.c_str()); print(s4);
//	sound_system_c s5(fmod_system, filename5.c_str()); print(s5);
//	sound_system_c s6(fmod_system, filename6.c_str()); print(s6);
//	sound_system_c s7(fmod_system, filename7.c_str()); print(s7);
//	sound_system_c s8(fmod_system, filename8.c_str()); print(s8);
//	sound_system_c s9(fmod_system, filename9.c_str()); print(s9);
//	sound_system_c s10(fmod_system, filename10.c_str()); print(s10);
//	sound_system_c s11(fmod_system, filename11.c_str()); print(s11);
//	sound_system_c s12(fmod_system, filename12.c_str()); print(s12);
//	sound_system_c s13(fmod_system, filename13.c_str()); print(s13);
//	sound_system_c s14(fmod_system, filename14.c_str()); print(s14);
//	sound_system_c s15(fmod_system, filename15.c_str()); print(s15);
//	sound_system_c s16(fmod_system, filename16.c_str()); print(s16);
//	sound_system_c s17(fmod_system, filename17.c_str()); print(s17);
//	sound_system_c s18(fmod_system, filename18.c_str()); print(s18);
//	sound_system_c s19(fmod_system, filename19.c_str()); print(s19);
//	sound_system_c s20(fmod_system, filename20.c_str()); print(s20);
//	sound_system_c s21(fmod_system, filename21.c_str()); print(s21);
//
//
//	s21.play_music();
//	s21.setVolume(0.2f);
//	s21.setIsPaused(false);
//
//	while (window.isOpen())
//	{
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//
//			if (event.type == sf::Event::KeyPressed)
//			{
//				if (event.key.code == sf::Keyboard::S)
//				{
//					std::cout << "\nStop";
//					s21.stop();
//				}
//				if (event.key.code == sf::Keyboard::P)
//				{
//					std::cout << "\nPause";
//					s21.pause();
//				}
//				if (event.key.code == sf::Keyboard::R)
//				{
//					std::cout << "\nPlay";
//					s21.play_music();
//				}
//			}
//		}
//
//		window.clear();
//		//s21.run();
//		//window.draw(s21.VA2);
//		window.display();
//	}
//
//	return 0;
//}


