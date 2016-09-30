#pragma once

#include <SFML/Graphics.hpp>


class Background
{
public:

	~Background();
	static Background* create();

	void draw(sf::RenderWindow& window) const;
	
protected:

	void createHexaGrid();
	void createGradientForGrid();
	
private:
	
	std::vector<sf::CircleShape> shapes;
	sf::Vertex* gradientVertices;
		
	explicit Background();
	Background(const Background&) = delete;
	Background& operator=(const Background&) = delete;

	void init();
};