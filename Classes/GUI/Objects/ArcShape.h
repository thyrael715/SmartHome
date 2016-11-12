#pragma once

#include <SFML\Graphics.hpp>
#include "Defaults.h"
#include "Node.h"


class ArcShape : public sf::Drawable, public Node
{
public:

	virtual ~ArcShape();

	static ArcShape* create(sf::Vector2f pos, size_t radius, size_t thickness, size_t fromAngle, size_t toAngle, sf::Color color = COLOR_WHITE);
	
protected:
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual sf::FloatRect getBoundingBox() const override;
	virtual bool init() override;
		
protected:
	
	ConcaveShape	m_arc;

	sf::Vector2f	m_pos;
	size_t			m_radius;
	size_t			m_thickness;
	size_t			m_fromAngle;
	size_t			m_toAngle;
	sf::Color		m_color;

	explicit		ArcShape();

	void			createWith();
};	