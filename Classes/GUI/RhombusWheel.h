#pragma once

#include <SFML\Graphics.hpp>
#include "Defaults.h"
#include "Object.h"

class RhombusWheel : public Object
{
public:

	virtual ~RhombusWheel();

	static RhombusWheel*	create(sf::Vector2f pos, float radius, size_t count, float w, float h, sf::Color color = COLOR_WHITE);

	virtual sf::FloatRect	getBoundingBox() const;
	//virtual void			setPosition(sf::Vector2f pos) override;
	//virtual void			setPosition(float posX, float posY) override;
	
	void					setColor(sf::Color color);
	sf::Color				getColor() const;
	void					setAnimAngle(float angle);
	void					setAnimCenter(sf::Vector2f center);
	void					startAnimation();
	void					stopAnimation();
	void					draw(sf::RenderWindow& window);

protected:

	explicit				RhombusWheel();

private:

	std::vector<sf::Shape*>	m_wheelShape;
	sf::Transform			m_transform;
	
	sf::Color				m_color;
	float					m_radius;
	float					m_width;
	float					m_height;
	unsigned int			m_wheelPartCount;

	// For animation

	float					m_animAngle;
	sf::Vector2f			m_animCenter;
	bool					m_isAnimating;

	void					createWheel();
	void					reCreate();
};