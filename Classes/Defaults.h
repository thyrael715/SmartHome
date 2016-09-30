#pragma once

// *** Includes ***

#include <string> 
#include <SFML/Graphics.hpp>

// *** Macros ***

#define STOI(S)		std::stoi(S)
#define ITOS(I)		std::to_string(I)

#define PI			3.14159265

#define COLOR_TRANSPARENT	sf::Color(0, 0, 0, 0)
#define COLOR_WHITE			sf::Color{255, 255, 255, 255}


// *** Typedefs ***

typedef std::vector<sf::ConvexShape> ConcaveShape;


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

private:

	sf::Vector2f		windowSize;
};
