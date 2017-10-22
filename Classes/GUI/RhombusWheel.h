#pragma once


#include "Object.h"


class RhombusWheel : public Object
{
public:

	RhombusWheel(float radius, size_t count, float rhombus_w, float rhombus_h);
	virtual ~RhombusWheel();

	void					setOutlineColor(sf::Color color);
	sf::Color				getOutlineColor() const;

	void					setRadius(float radius);
	float					getRadius() const;

	void					setWheelPartCount(size_t wheelPartCount);
	size_t					getWheelPartCount() const;

	// Animation

	void					setAnimationSpeed(float angle);
	void					startAnimation();
	void					stopAnimation();

public:

	virtual void onUpdate(float dt) override;

private:
		
	// Properties of RhombusWheel

	sf::Color				m_outlineColor;
	float					m_radius;
	float					m_rhombusHeight;
	float					m_rhombusWidth;
	size_t					m_wheelPartCount;

	// For animation

	float					m_animationSpeed;
	bool					m_isAnimating;

private:

	void					reCreate();
};