#include "Defaults.h"

Defaults::Defaults()
	: m_windowSize(0, 0)
	, m_mainView(nullptr)
{
	m_mainView = new sf::View();
}

Defaults::~Defaults()
{
	SAFE_DELETE(m_mainView);
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

	if (m_mainView)
	{
		m_mainView->reset(sf::FloatRect(0, 0, x, y));
	}
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

sf::View& Defaults::getMainView() const
{
	return *m_mainView;
}