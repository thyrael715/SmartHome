#include "Scheduler.h"


Scheduler::Scheduler()
{

}


Scheduler* Scheduler::getInstance()
{
	static Scheduler* ret = new Scheduler();
	return ret;
}


void Scheduler::update(float dt)
{
	for (auto it = m_objsToBeUpdated.begin(); it != m_objsToBeUpdated.end(); ++it)
	{
		it->second->callback(dt);
	}
}
