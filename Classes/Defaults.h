#pragma once

// *** Includes ***

#include <string> 
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Maths.h"

// *** Macros ***

#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
	__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
	if (pRet) \
	{ \
		pRet->init(); \
	} \
	else \
	{ \
		SAFE_DELETE(pRet) \
	} \
	return pRet; \
} \

#define STOI(S) std::stoi(S)
#define ITOS(I) std::to_string(I)

#define WINDOW_WIDTH  Defaults::getInstance()->getWindowWidth()
#define WINDOW_HEIGHT Defaults::getInstance()->getWindowHeight()

#define C2WW(v) static_cast<decltype(v)>(floorf(Defaults::getInstance()->getWindowWidth() * \
										(v / Defaults::getInstance()->getWindowWidth())))

#define C2WH(v) static_cast<decltype(v)>(floorf(Defaults::getInstance()->getWindowHeight() * \
										(v / Defaults::getInstance()->getWindowHeight())))

#define COLOR_TRANSPARENT		sf::Color(0, 0, 0, 0)
#define COLOR_WHITE				sf::Color(255, 255, 255)
#define COLOR_BASECOLOR_CIAN	sf::Color(0, 174, 175)
#define COLOR_BASECOLOR_BLUE	sf::Color(2, 186, 248)

#define CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

#define SAFE_DELETE(p) if (p != nullptr) {delete p; p = nullptr;}
#define SAFE_DELETE_VECTOR(v) Defaults::getInstance()->safeVectorReleaser(v);



class Defaults
{
private:

	Defaults();

public:
		
	Defaults(const Defaults&) = delete;
	Defaults& operator=(const Defaults&) = delete;

	static Defaults*	getInstance();

	void				setWindowSize(float x, float y);
	sf::Vector2f		getWindowSize() const;
	float				getWindowWidth() const;
	float				getWindowHeight() const;

	template<typename T>
	void safeVectorReleaser(std::vector<T*>& v);

private:

	sf::Vector2f		m_windowSize;
};



template<typename T>
void Defaults::safeVectorReleaser(std::vector<T*>& v)
{
	if (v.size() == 0)
		return;

	for (auto it = v.begin(); it != v.end(); ++it)
	{
		delete (*it);
	}

	v.clear();
}
