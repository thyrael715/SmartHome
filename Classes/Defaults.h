#pragma once

// *** Includes ***

#include <string> 
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Maths.h"

// *** Macros ***

#define STOI(S) std::stoi(S)
#define ITOS(I) std::to_string(I)

#define WINDOW_WIDTH  Defaults::getInstance()->getWindowWidth()
#define WINDOW_HEIGHT Defaults::getInstance()->getWindowHeight()

#define C2WW(v) static_cast<decltype(v)>(floorf(Defaults::getInstance()->getWindowWidth() * \
										(v / Defaults::getInstance()->getWindowWidth())))

#define C2WH(v) static_cast<decltype(v)>(floorf(Defaults::getInstance()->getWindowHeight() * \
										(v / Defaults::getInstance()->getWindowHeight())))

#define PI 3.14159265

#define COLOR_TRANSPARENT	sf::Color(0, 0, 0, 0)
#define COLOR_WHITE			sf::Color{255, 255, 255, 255}

#define CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

#define SAFE_DELETE(p) if (p != nullptr) {delete p; p = nullptr;}



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
	void				safeVectorReleaser(std::vector<T*>& v) const;

private:

	sf::Vector2f		m_windowSize;
};



template<typename T>
void Defaults::safeVectorReleaser(std::vector<T*>& v) const
{
	if (v.size() == 0)
		return;

	for (auto it = v.begin(); it != v.end(); ++it)
	{
		delete (*it);
	}

	v.clear();
}