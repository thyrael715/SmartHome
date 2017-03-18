#ifndef __CENTRAL_LAYER_H__
#define __CENTRAL_LAYER_H__

#include <cocos2d.h>


class CentralLayer : public cocos2d::Layer
{
public:

	CREATE_FUNC(CentralLayer);

protected:

	virtual bool init();

private:

	void createOuterPart();
};

#endif __CENTRAL_LAYER_H__
