#pragma once


#include "Object.h"


class BackgroundLayer : public Object
{
public:

	CREATE_FUNC(BackgroundLayer);

	BackgroundLayer();
	virtual ~BackgroundLayer();

	void init();

protected:

	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates& states) const override;
	
protected:

	void createHexaGrid();
	void createGradientForGrid();
	
private:

	std::vector<sf::CircleShape> shapes;
	sf::Vertex* gradientVertices;
};