#include "Defaults.h"


Defaults* Defaults::getInstance()
{
	static Defaults *d = new Defaults();
	return d;
}
