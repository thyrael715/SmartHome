#pragma once


#include "RhombusWheel.h"
#include "ArcShape.h"
#include "ButtonArc.h"


class CentralPanel : public Object
{
public:

	CREATE_FUNC(CentralPanel)

	CentralPanel();
	virtual ~CentralPanel();

	void init();

private:

	void createInnerCircle();
	void createCentralCircleMenu();

private:

	std::vector<ButtonArc*>	m_mainButtons;
};