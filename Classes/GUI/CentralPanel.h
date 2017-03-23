#pragma once

#include <SFML/Graphics.hpp>
#include "RhombusWheel.h"
#include "ArcShape.h"
#include "ButtonArc.h"

class CentralPanel
{
public:

	~CentralPanel();
	static CentralPanel* create();

	void draw(sf::RenderWindow& window) const;

protected:

private:

	RhombusWheel*			m_wheelShape;
	std::vector<ArcShape*>	m_outerArc;
	std::vector<ButtonArc*>	m_mainButtons;

	explicit			CentralPanel();

	void				init();
	void				createCentralCircleMenu();
};