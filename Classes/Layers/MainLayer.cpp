#include "MainLayer.h"
#include "BackgroundLayer.h"
#include "CentralLayer.h"
#include <iostream>


USING_NS_CC;

Scene* MainLayer::createScene()
{
    auto scene = Scene::create();
	auto layer = MainLayer::create();

    scene->addChild(layer);

    return scene;
}

bool MainLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	BackgroundLayer* bg = BackgroundLayer::create();
	this->addChild(bg);

	CentralLayer* c = CentralLayer::create();
	this->addChild(c);
        
    return true;
}
