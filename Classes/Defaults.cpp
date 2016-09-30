#include "Defaults.h"

Defaults::Defaults()
	: windowSize(0, 0)
{

}

Defaults* Defaults::getInstance()
{
	static Defaults *d = new Defaults();
	return d;
}

void Defaults::setWindowSize(float x, float y)
{
	windowSize.x = x;
	windowSize.y = y;
}

sf::Vector2f Defaults::getWindowSize() const
{
	return windowSize;
}

float Defaults::getWindowWidth() const
{
	return windowSize.x;
}

float Defaults::getWindowHeight() const
{
	return windowSize.y;
}