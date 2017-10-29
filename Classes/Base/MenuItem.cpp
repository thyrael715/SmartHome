#include "MenuItem.h"


MenuItem::MenuItem()
	: onActivate(nullptr)
	, onDeactivate(nullptr)
	, onSelect(nullptr)
	, onUnselect(nullptr)
{

}

MenuItem::~MenuItem()
{
	onActivate = nullptr;
	onDeactivate = nullptr;
	onSelect = nullptr;
	onUnselect = nullptr;
}
