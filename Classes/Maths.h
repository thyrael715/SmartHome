#pragma once

#include <SFML\Graphics.hpp>


#define PI 3.14159265

class Maths
{
public:

	virtual ~Maths();

	static bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
	static bool doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2);
	static bool isInside(const sf::VertexArray& polygon, sf::Vector2f p);
	static bool isInRect(const sf::FloatRect& rect, const sf::Vector2f& point);

	static float getDistance(sf::Vector2f a, sf::Vector2f b);

protected:

	explicit Maths();
	static int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);

private:

	Maths(const Maths&) = delete;
	Maths* operator=(const Maths&) = delete;
};