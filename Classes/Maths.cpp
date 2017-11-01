#include "Maths.h"
#include <iostream>

using namespace std;


#define INF 10000


Maths::Maths()
{

}

Maths::~Maths()
{

}

int Maths::orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	float val = (q.y - p.y) * (r.x - q.x) -
			  (q.x - p.x) * (r.y - q.y);

	if (val == 0.0f) 
		return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool Maths::onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
	{
		return true;
	}

	return false;
}

bool Maths::doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) 
		return true;

	// p1, q1 and p2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1))
		return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) 
		return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) 
		return true;

	return false; // Doesn't fall in any of the above cases
}


// Returns true if the point p lies inside the polygon[] with n vertices
bool Maths::isInside(const sf::VertexArray& polygon, sf::Vector2f p)
{
	// There must be at least 3 vertices in polygon[]
	if (polygon.getVertexCount() < 3)
		return false;

	// Create a point for line segment from p to infinite
	sf::Vector2f extreme = { INF, p.y };

	// Count intersections of the above line with sides of polygon
	int count = 0, i = 0;

	do
	{
		int next = (i + 1) % polygon.getVertexCount();

		// Check if the line segment from 'p' to 'extreme' intersects
		// with the line segment from 'polygon[i]' to 'polygon[next]'
		if (doIntersect(polygon[i].position, polygon[next].position, p, extreme))
		{
			// If the point 'p' is colinear with line segment 'i-next',
			// then check if it lies on segment. If it lies, return true,
			// otherwise false
			if (orientation(polygon[i].position, p, polygon[next].position) == 0)
			{
				return onSegment(polygon[i].position, p, polygon[next].position);
			}

			count++;
		}

		i = next;
	} 
	while (i != 0);

	// Return true if count is odd, false otherwise
	return count & 1;  // Same as (count%2 == 1)
}


bool Maths::isInRect(const sf::FloatRect& rect, const sf::Vector2f& point)
{
	if (rect.left > point.x ||
		rect.top > point.y ||
		rect.left + rect.width < point.x ||
		rect.top + rect.height < point.y)
	{
		return false;
	}

	return true;
}


float Maths::getDistance(sf::Vector2f a, sf::Vector2f b)
{
	const float r1 = pow((a.x - b.x), 2.0f);
	const float r2 = pow((a.y - b.y), 2.0f);

	return sqrt(r1 + r2);
}