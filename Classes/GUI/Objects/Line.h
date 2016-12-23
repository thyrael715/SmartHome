#pragma once

#include "SFML/Graphics.hpp"
#include "Object.h"

//class Line : public sf::Drawable, public Object
//{
//public:
//
//	virtual ~Line();
//	virtual sf::FloatRect getBoundingBox() const override;
//
//	static Line* create(sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color = COLOR_WHITE);
//
//protected:
//	
//	virtual bool init() override;
//	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
//
//protected:
//
//	sf::RectangleShape m_rect;
//		
//	explicit Line();
//
//private:
//
//	void createWith(sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color);
//};