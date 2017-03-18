#include "Shapes.h"

USING_NS_CC;
using namespace Shapes;


IShapes::IShapes()
	: p_drawNode(nullptr)
{
	p_drawNode = DrawNode::create();
}

IShapes::~IShapes()
{
	CC_SAFE_DELETE(p_drawNode);
}


#define PI			3.14159265

bool Arc::init()
{
	if (!IShapes::init())
	{
		return false;
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glLineWidth(1);

	p_drawNode->setPosition(700, 500);

	for (float k = 0; k < 360; k += 1)
	{
		float x1 = (float)(cos(k * PI / 180.0f) * 100);
		float y1 = (float)(sin(k * PI / 180.0f) * 100);

		float x2 = (float)(cos(k * PI / 180.0f) * 101);
		float y2 = (float)(sin(k * PI / 180.0f) * 101);

		p_drawNode->drawSegment(Vec2(x1, y1), Vec2(x2, y2), 2, Color4F::WHITE);
	}

	//p_drawNode->drawSolidCircle(Vec2(120, 120), 100, 0, 100, Color4F::WHITE);
	//p_drawNode->drawCircle(Vec2(120, 120), 100, 0, 100, false, 1, 1, Color4F::WHITE);

	m_vertices.clear();

	float r1 = 0.0f, r2 = 0.0f;
	float m_fromAngle = 0;
	float m_toAngle = 270;
	size_t m_thickness = 20;
	float radius = 100;

	if (m_thickness > 1)
	{
		r1 = radius + static_cast<size_t>(m_thickness / 2);
		r2 = radius - static_cast<size_t>(m_thickness / 2);
	}
	else
	{
		r1 = radius;
		r2 = radius - m_thickness;
	}

	auto tempNode = DrawNode::create();
	tempNode->setPosition(800, 300);

	auto tempNode2 = DrawNode::create();
	tempNode2->setPosition(300, 300);

	for (float k = m_fromAngle; k < m_toAngle; k += 1)
	{
		float x1 = (float)(cos(k * PI / 180.0f) * r1);
		float y1 = (float)(sin(k * PI / 180.0f) * r1);

		float x2 = (float)(cos(k * PI / 180.0f) * r2);
		float y2 = (float)(sin(k * PI / 180.0f) * r2);

		m_vertices.push_back(Vec2(x1, y1));
		m_vertices.push_back(Vec2(x2, y2));
	}

	m_thickness = 19;

	if (m_thickness > 1)
	{
		r1 = radius + static_cast<size_t>(m_thickness / 2);
		r2 = radius - static_cast<size_t>(m_thickness / 2);
	}
	else
	{
		r1 = radius;
		r2 = radius - m_thickness;
	}

	for (float k = m_fromAngle; k < m_toAngle; k += 1)
	{
		float x1 = (float)(cos(k * PI / 180.0f) * r1);
		float y1 = (float)(sin(k * PI / 180.0f) * r1);

		float x2 = (float)(cos(k * PI / 180.0f) * r2);
		float y2 = (float)(sin(k * PI / 180.0f) * r2);

		tempNode->drawSegment(Vec2(x1, y1), Vec2(x2, y2), 2, Color4F::WHITE);
	}


	for (size_t i = 0; i < m_vertices.size() - 2; i++)
	{
		Vec2 temp[3] = { m_vertices[i], m_vertices[i + 1], m_vertices[i + 2] };
		tempNode2->drawSolidPoly(temp, 3, Color4F::RED);
	}

	this->addChild(p_drawNode);
	this->addChild(tempNode);
	this->addChild(tempNode2);








	//auto renderTexture = RenderTexture::create(400, 400);
	//renderTexture->beginWithClear(0, 0, 0, 0); // black
	//auto drawPrimitive = DrawNode::create();
	//drawPrimitive->retain();
	////drawPrimitive->drawDot(Point(10, 10), 2, Color4F::RED);
	//drawPrimitive->drawSolidCircle(Vec2(100, 100), 100, 0, 100, Color4F::WHITE);
	//drawPrimitive->visit();
	//renderTexture->end();
	//renderTexture->retain();
	//renderTexture->setPosition(1600 / 2, 900 / 2);
	//this->addChild(renderTexture, 10000);





	return true;
}

