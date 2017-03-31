#pragma once

#include <SFML/Graphics.hpp>
#include "RhombusWheel.h"
#include "ArcShape.h"
#include "ButtonArc.h"

class CentralPanel : public Object
{
public:

	CentralPanel();
	virtual ~CentralPanel();

protected:

	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates& states) const override;

private:

	virtual void init() override;
	void createCentralCircleMenu();

private:

	std::vector<ArcShape*>	m_outerArc;
	std::vector<ButtonArc*>	m_mainButtons;
};