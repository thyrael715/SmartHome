#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"


class Background : public Object
{
public:

	Background();
	virtual ~Background();
	virtual void init() override;

	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates& states) const override;
	
protected:

	void createHexaGrid();
	void createGradientForGrid();
	
private:

	std::vector<sf::CircleShape> shapes;
	sf::Vertex* gradientVertices;
};