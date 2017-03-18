#ifndef __MAINLAYER_H__
#define __MAINLAYER_H__

#include "cocos2d.h"


class MainLayer : public cocos2d::Layer
{
public:

	CREATE_FUNC(MainLayer);

    static cocos2d::Scene* createScene();

protected:

    virtual bool init();
    
};

#endif // __MAINLAYER_H__
