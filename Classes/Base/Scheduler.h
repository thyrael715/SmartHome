#pragma once 


#include <map>
#include <functional>



class Scheduler
{
	typedef std::function<void()> Callback;

	struct ScheduleElement
	{
		int priority;
		void* target;
		std::function<void(float dt)> callback;
	};

public:

	static Scheduler* getInstance();

	void update(float dt);

	template <class T>
	void scheduleUpdate(T* obj)
	{
		scheduleUpdateWithPriority(obj, 0);
	}


	template <class T>
	void scheduleUpdateWithPriority(T* target, int priority)
	{
		ScheduleElement* e = new ScheduleElement();
		e->target = target;
		e->priority = priority;
		e->callback = [target](float dt)
		{
			target->onUpdate(dt);
		};

		m_objsToBeUpdated.emplace(priority, e);
	}


	template <class T>
	void unscheduleUpdate(T* obj)
	{
		for (auto it = m_objsToBeUpdated.begin(); it != m_objsToBeUpdated.end(); ++it)
		{
			if (it->second == obj)
			{
				delete it->second;
				m_objsToBeUpdated.erase(it);
				break;
			}
		}
	}
	
private:

	explicit Scheduler();
	Scheduler(const Scheduler& s) = delete;
	Scheduler& operator=(const Scheduler& s) = delete;
	
private:

	std::multimap<int, ScheduleElement*> m_objsToBeUpdated;
};