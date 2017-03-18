#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__


#include <cocos2d.h>

class BackgroundLayer : public cocos2d::LayerColor
{
public:

	CREATE_FUNC(BackgroundLayer);

protected:

	virtual bool init();

private:

	void createHexaGrid();
	void createFullGradientMask();
	cocos2d::LayerGradient* createGradientMask(const cocos2d::Vec2& pos, 
											   const cocos2d::Size& size, 
											   const cocos2d::Color4B& start, 
											   const cocos2d::Color4B& end,
											   const cocos2d::Vec2& direction);
};

#endif //__BACKGROUND_LAYER_H__