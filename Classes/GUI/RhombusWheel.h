#pragma once

#include <SFML\Graphics.hpp>
#include "Defaults.h"

class RhombusWheel
{
public:

	RhombusWheel();
	~RhombusWheel();

	static RhombusWheel* create(sf::Vector2f pos, float radius, size_t count, float w, float h, sf::Color color = COLOR_WHITE);

	void			setColor(sf::Color color);
	sf::Color		getColor() const;

	void			setPosition(sf::Vector2f pos);
	void			setPositionX(float posX);
	void			setPositionY(float posY);
	sf::Vector2f	getPosition() const;

	void			setAnimAngle(float angle);
	void			setAnimCenter(sf::Vector2f center);
	void			startAnimation();
	void			stopAnimation();

	void			draw(sf::RenderWindow& window);

private:

	ConcaveShape	m_wheelShape;
	sf::Transform	m_transform;
	
	sf::Vector2f	m_pos;
	sf::Color		m_color;
	float			m_radius;
	float			m_width;
	float			m_height;
	unsigned int	m_wheelPartCount;

	// For animation
	float			m_animAngle;
	sf::Vector2f	m_animCenter;
	bool			m_isAnimating;

	void			createWheel();
	void			reCreate();
};