#pragma once 
 
// ***** Includes ***** 
 
#include <string> 
#include <sapi.h> 
#include <sphelper.h> 
#include <iostream> 
#include "tx.h"
 
// ***** Constants ***** 
 
const DWORD BREAK_BETWEEN_SENTENCES = 500; 
 
// ***** Speaker Class implemetation ***** 
 
class Speaker 
{ 
 
private: 
 
	Speaker();  
 
	bool init(); 
	void speak(LPCWSTR wstr); 
 
public: 
 
	// Functions 
 
	~Speaker(); 
	Speaker(const Speaker&) = delete; 
	Speaker& operator=(const Speaker&) = delete; 
 
	static Speaker* getInstance(); 
 
	void say(const std::string str);
 
private: 
 
	// Variables 
 
	ISpVoice* p_voice; 
 
}; 