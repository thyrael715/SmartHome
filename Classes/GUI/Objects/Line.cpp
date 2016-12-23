#include "Line.h"

//Line::Line()
//	: m_thickness(0.0f)
//{
//
//}
//
//Line::~Line()
//{
//
//}
//
//sf::FloatRect Line::getBoundingBox() const
//{
//	return sf::FloatRect(0, 0, 0, 0);
//}
//
//Line* Line::create(sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color)
//{
//	Line *ret = new (std::nothrow) Line();
//
//	if (ret && ret->init())
//	{
//		ret->createWith(start, end, thickness, color);
//		return ret;
//	}
//
//	return nullptr;
//}
//
//void Line::createWith(sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color)
//{
//	float width = std::sqrt(std::pow(end.x - start.x, 2.0f) + std::pow(end.y - start.y, 2.0f));
//	
//	m_rect.setSize(sf::Vector2f(width, thickness));
//	m_rect.setPosition(start);
//	m_rect.setFillColor(color);
//}
//
//bool Line::init()
//{
//	return true;
//}
//
//void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	target.draw(m_rect);
//}