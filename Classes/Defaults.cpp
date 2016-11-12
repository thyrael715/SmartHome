#include "Defaults.h"

Defaults::Defaults()
	: m_windowSize(0, 0)
{

}

Defaults* Defaults::getInstance()
{
	static Defaults *d = new Defaults();
	return d;
}

void Defaults::setWindowSize(float x, float y)
{
	m_windowSize.x = x;
	m_windowSize.y = y;
}

sf::Vector2f Defaults::getWindowSize() const
{
	return m_windowSize;
}

float Defaults::getWindowWidth() const
{
	return m_windowSize.x;
}

float Defaults::getWindowHeight() const
{
	return m_windowSize.y;
}