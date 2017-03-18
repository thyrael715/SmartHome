/*
* Includes
*/

#include "CentralLayer.h"
#include "Shapes.h"

/*
* Namespaces
*/

USING_NS_CC;

/*
* Defines
*/


/*
* CentralLayer member functions
*/

bool CentralLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	createOuterPart();

	return true;
}

void CentralLayer::createOuterPart()
{
	auto arcShape = Shapes::Arc::create();

	this->addChild(arcShape);
}