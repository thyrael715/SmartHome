#pragma once

#include <SFML/Graphics.hpp>
#include "RhombusWheel.h"

class CentralPanel
{
public:

	~CentralPanel();
	static CentralPanel* create();

	void draw(sf::RenderWindow& window) const;

protected:

private:
	
	RhombusWheel* m_wheelShape;
	ConcaveShape m_arc;

	void init();
	void createWheel();

	explicit CentralPanel();
	CentralPanel(const CentralPanel&) = delete;
	CentralPanel& operator=(const CentralPanel&) = delete;
};