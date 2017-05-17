#pragma once


#include "Shape.h"


class WaveForm : public Object
{
	enum Type
	{
		NONE,
		CIRCLE,
		LINE
	};

public:

	WaveForm(Type type, float thickness, size_t resolution = 360);
	virtual ~WaveForm();

private:

	Type m_type;
	std::list<Shape*> m_waveLine;
	size_t m_resolution;
	float m_thickness;
};