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

#define WINDOW_WIDTH  Defaults::getInstance()->getRenderWindow()->getSize().x
#define WINDOW_HEIGHT Defaults::getInstance()->getRenderWindow()->getSize().y

#define MOUSE_ABSOLUTE_POS sf::Mouse::getPosition()
#define MOUSE_ABSOLUTE_POS_X sf::Mouse::getPosition().x
#define MOUSE_ABSOLUTE_POS_Y sf::Mouse::getPosition().y

#define MOUSE_RELATIVE_POS   sf::Mouse::getPosition(*(Defaults::getInstance()->getRenderWindow()))
#define MOUSE_RELATIVE_POS_X sf::Mouse::getPosition(*(Defaults::getInstance()->getRenderWindow())).x
#define MOUSE_RELATIVE_POS_Y sf::Mouse::getPosition(*(Defaults::getInstance()->getRenderWindow())).y

#define C2WW(v) static_cast<decltype(v)>(floorf((float)(Defaults::getInstance()->getRenderWindow()->getSize().x) * \
										(v / (float)(Defaults::getInstance()->getRenderWindow()->getSize().x))))

#define C2WH(v) static_cast<decltype(v)>(floorf((float)(Defaults::getInstance()->getRenderWindow()->getSize().y) * \
										(v / (float)(Defaults::getInstance()->getRenderWindow()->getSize().y))))

#define COLOR_TRANSPARENT		sf::Color(0, 0, 0, 0)
#define COLOR_WHITE				sf::Color(255, 255, 255)
#define COLOR_BASECOLOR_CIAN	sf::Color(0, 174, 175)
#define COLOR_BASECOLOR_BLUE	sf::Color(2, 186, 248)

#define ZERO	sf::Vector2f(0.0f, 0.0f)

#define CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

#define SAFE_DELETE(p) if (p != nullptr) {delete p; p = nullptr;}
#define SAFE_DELETE_CONTAINER(v) Defaults::getInstance()->safeContainerReleaser(v);


enum Orientation
{
	UNKNOWN,
	HORIZONTAL,
	VERTICAL
};



class Defaults
{
private:

	Defaults();
	~Defaults();

	Defaults(const Defaults&) = delete;
	Defaults& operator=(const Defaults&) = delete;

public:

	static Defaults*	getInstance();

	void				setRenderWindow(sf::RenderWindow* renderWindow);
	sf::RenderWindow*	getRenderWindow() const;
		
	template<typename C_Type>
	void safeContainerReleaser(C_Type & v);

private:

	sf::RenderWindow*	m_mainWindow;
};


template<typename C_Type>
void Defaults::safeContainerReleaser(C_Type & v)
{
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		delete (*it);
	}

	v.clear();
}
