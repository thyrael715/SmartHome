#pragma once

#include <SFML\Graphics.hpp>
#include "Defaults.h"
#include "Node.h"


class ArcShape : public sf::Drawable, public Node
{
public:

	virtual ~ArcShape();

	static ArcShape*		create(sf::Vector2f pos, size_t radius, size_t thickness, size_t fromAngle, size_t toAngle, sf::Color color = COLOR_WHITE);
	
	void					setColor(sf::Color color);
	sf::Color				getColor() const;
	void					setPosition(sf::Vector2f vec);
	void					setPosition(float x, float y);
	sf::Vector2f			getPosition() const;
		
protected:
	
	virtual bool			init() override;	
	virtual sf::FloatRect	getBoundingBox() const override;
	virtual bool			contains(const sf::Vector2f& point) const override;
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		
protected:
	
	std::vector<sf::Vertex> m_arc;

	sf::Vector2f			m_pos;
	size_t					m_radius;
	size_t					m_thickness;
	size_t					m_fromAngle;
	size_t					m_toAngle;
	sf::Color				m_color;

	explicit				ArcShape();
	void					createWith();
};	