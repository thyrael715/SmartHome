#pragma once

#include <SFML\Graphics.hpp>
#include "Defaults.h"
#include "Object.h"

class RhombusWheel : public Object , public sf::Drawable
{
public:

	RhombusWheel(float radius, size_t count, float w, float h);
	virtual ~RhombusWheel();

	virtual sf::FloatRect	getGlobalBounds() const;
	virtual bool			contains(const sf::Vector2f& point) const;
	
	void					setOutlineColor(sf::Color color);
	sf::Color				getOutlineColor() const;

	void					setRadius(float radius);
	float					getRadius() const;

	void					setWidth(float width);
	float					getWidth() const;

	void					setHeight(float height);
	float					getHeight() const;

	void					setWheelPartCount(size_t wheelPartCount);
	size_t					getWheelPartCount() const;

	// Animation

	void					setAnimAngle(float angle);
	void					setAnimCenter(sf::Vector2f center);
	void					startAnimation();
	void					stopAnimation();

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	std::vector<sf::ConvexShape*>	m_wheelShape;
	
	// Properties of RhombusWheel

	sf::Color				m_outlineColor;
	float					m_radius;
	float					m_width;
	float					m_height;
	size_t					m_wheelPartCount;

	// For animation

	float					m_animAngle;
	sf::Vector2f			m_animCenter;
	bool					m_isAnimating;

private:

	void					create();
	void					reCreate();
	void					update();
};