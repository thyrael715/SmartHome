#include "Defaults.h"

Defaults::Defaults()
	: m_mainWindow(nullptr)
{

}


Defaults::~Defaults()
{
	m_mainWindow = nullptr;
}


Defaults* Defaults::getInstance()
{
	static Defaults *d = new Defaults();	
	return d;
}


void Defaults::setRenderWindow(sf::RenderWindow* renderWindow)
{
	m_mainWindow = renderWindow;
}


sf::RenderWindow* Defaults::getRenderWindow() const
{
	return m_mainWindow;
}