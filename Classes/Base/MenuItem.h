#pragma once

#include "Object.h"


class MenuItem : public Object
{
	typedef std::function<void()> Callback;

public:

	MenuItem();
	~MenuItem();

	Callback onActivate;
	Callback onDeactivate;
	Callback onSelect;
	Callback onUnselect;
};