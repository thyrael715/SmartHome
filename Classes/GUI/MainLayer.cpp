#include "MainLayer.h"
#include "BackgroundLayer.h"
#include "CentralPanel.h"


void MainLayer::init()
{
	BackgroundLayer *bg = BackgroundLayer::create();
	this->addChild(bg, 100);

	CentralPanel* cp = CentralPanel::create();
	cp->setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
	this->addChild(cp);
}