/*
* Includes
*/

#include "BackgroundLayer.h"

/*
* Defines
*/

#define COLOR_BACKGROUND		Color4B(20, 20, 20, 255)
#define COLOR_HEXAGRID			Color4F(0.0f, 0.0f, 0.0f, 1.0f)
#define COLOR_GRAD_TRANSPARENT	Color4B(0, 0, 0, 0)
#define COLOR_GRAD_BLACK		Color4B(0, 0, 0, 150)

#define GRADIENT_SIZE			212
#define EXTENTED_BOUNDINGSIZE	20

/*
* Namespaces
*/

USING_NS_CC;

/*
* BackgroundLayer member functions
*/

bool BackgroundLayer::init()
{
	if (!LayerColor::initWithColor(COLOR_BACKGROUND)) //RGBA
	{
		return false;
	}

	// Resize and reposition the layer
	Vec2 newPos = this->getPosition() + Vec2(-EXTENTED_BOUNDINGSIZE, -EXTENTED_BOUNDINGSIZE);
	Size newSize = this->getContentSize() + Size(2 * EXTENTED_BOUNDINGSIZE, 2 * EXTENTED_BOUNDINGSIZE);

	this->setPosition(newPos);
	this->setContentSize(newSize);
	
	// Create hexagonal grid and a gradient mask above it
	createHexaGrid();
	createFullGradientMask();

	return true;
}


void BackgroundLayer::createHexaGrid()
{
	const float lineWidth = 1.0f;
	const float angle = 0;
	const float radius = 10;
	const unsigned int segments = 6;
	const unsigned int scaleX = 1, scaleY = 1;

	const size_t shiftX = static_cast<size_t>((3 * radius) + (2 * lineWidth));
	const size_t shiftY = static_cast<size_t>((2 * ((sqrt(3.0f) / 2.0f) * radius)) + (2 * lineWidth));

	size_t countX = static_cast<size_t>(this->getContentSize().width / shiftX);
	size_t countY = static_cast<size_t>(this->getContentSize().height / shiftY);


	DrawNode *hexaGrid = DrawNode::create(lineWidth);

	for (size_t i = 0; i < countY; i++)
	{
		for (size_t j = 0; j < countX; j++)
		{
			Vec2 pos;

			pos = Vec2((float)(j*shiftX), (float)(i*shiftY));
			hexaGrid->drawSolidCircle(pos, radius, angle, segments, scaleX, scaleY, COLOR_HEXAGRID);

			pos = Vec2((float)(j*shiftX + ((1.5f * radius) + lineWidth)), (float)(i*shiftY + (((sqrt(3.0f) / 2.0f) * radius))));
			hexaGrid->drawSolidCircle(pos, radius, angle, segments, scaleX, scaleY, COLOR_HEXAGRID);
		}
	}

	this->addChild(hexaGrid);
}


void BackgroundLayer::createFullGradientMask()
{
	// Bot gradient mask
	auto bot = createGradientMask(Vec2(0.0f, 0.0f), 
								  Size(this->getContentSize().width, GRADIENT_SIZE), 
								  COLOR_GRAD_TRANSPARENT,
								  COLOR_GRAD_BLACK,
								  Vec2(0.0f, -1.0f));
	this->addChild(bot);

	// Top gradient mask
	auto top = createGradientMask(Vec2(0.0f, this->getContentSize().height - GRADIENT_SIZE),
								  Size(this->getContentSize().width, GRADIENT_SIZE), 
								  COLOR_GRAD_TRANSPARENT,
								  COLOR_GRAD_BLACK,
								  Vec2(0.0f, 1.0f));
	this->addChild(top);

	// Left gradient mask
	auto left = createGradientMask(Vec2(0, 0),
								   Size(GRADIENT_SIZE, this->getContentSize().height),
								   COLOR_GRAD_TRANSPARENT,
								   COLOR_GRAD_BLACK,
								   Vec2(-1.0f, 0.0f));
	this->addChild(left);

	// Left gradient mask
	auto right = createGradientMask(Vec2(this->getContentSize().width - GRADIENT_SIZE, 0.0f),
									Size(GRADIENT_SIZE, this->getContentSize().height),
									COLOR_GRAD_TRANSPARENT,
									COLOR_GRAD_BLACK,
									Vec2(1.0f, 0.0f));
	this->addChild(right);
}


LayerGradient* BackgroundLayer::createGradientMask(const Vec2& pos, const Size& size, const Color4B& start, const Color4B& end, const Vec2& direction)
{
	LayerGradient* layerGradient = LayerGradient::create(start, end, direction);

	if (layerGradient)
	{
		layerGradient->setContentSize(size);
		layerGradient->setPosition(pos);

		return layerGradient;
	}
	
	return nullptr;
}