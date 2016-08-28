#include "Speaker.h" 
#include <fstream> 
#include <iostream> 
#include <string> 
#include <cstdarg>
 
Speaker::Speaker() 
	: p_voice(nullptr) 
{ 
	init(); 
} 
 
Speaker::~Speaker() 
{ 
	if (p_voice) 
	{ 
		p_voice->Release(); 
		p_voice = nullptr; 
		CoUninitialize(); 
	} 
} 
 
Speaker* Speaker::getInstance() 
{ 
	static Speaker* sp = new Speaker(); 
	return sp; 
} 
 
bool Speaker::init() 
{ 
	if (FAILED(CoInitialize(NULL))) 
		return FALSE; 
 
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&p_voice); 
	
	if (!SUCCEEDED(hr)) 
		return FALSE; 
 
	return TRUE; 
} 
 
void Speaker::speak(LPCWSTR wstr) 
{ 
	if (p_voice) 
	{ 
		p_voice->Speak(wstr, 0, NULL); 
		Sleep(BREAK_BETWEEN_SENTENCES); 
	} 
} 
 
void Speaker::say(const std::string str)
{ 
	std::wstring resStr(str.begin(), str.end());
	speak(resStr.c_str());
} 