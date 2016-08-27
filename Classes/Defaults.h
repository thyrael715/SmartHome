#pragma once

// *** Includes ***

#include <string> 

// *** Macros ***

#define STOI(S)  std::stoi(S)
#define ITOS(I)  std::to_string(I)


class Defaults
{
private:

	Defaults(){};

public:

	Defaults(const Defaults&) = delete;
	Defaults& operator=(const Defaults&) = delete;

	static Defaults* getInstance();
};
