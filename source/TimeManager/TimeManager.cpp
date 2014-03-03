#include "stdafx.h"
#include "TimeManager.h"

#include "TimeObject/TimeObject.h"

namespace FG
{
	TimeManager::TimeManager() : currentTime(0), dt(0) {}

	void TimeManager::StartTimer()
	{
		for(auto* object : timeObjects)
		{
			//object->StartTimer(0);
		}
	}
	void TimeManager::EndTimer()
	{
		for(auto* object : timeObjects)
		{
			object->EndTimer();
		}
	}
	void TimeManager::Update(long currentTime)
	{
		dt = currentTime - this->currentTime;
		this->currentTime = currentTime;

		for(auto* object : timeObjects)
		{
			object->Update(currentTime);
		}
	}

	void TimeManager::RegisterTimeObject(TimeObject* object)
	{
		object->StartTimer(currentTime);
		timeObjects.push_back(object);
	}
	void TimeManager::UnregisterTimeObject(TimeObject* object)
	{
		for(auto it = timeObjects.begin(); it != timeObjects.end(); ++it)
		{
			if(*it == object)
			{
				timeObjects.erase(it);
				return;
			}
		}
	}
	void TimeManager::ClearTimeObjects()
	{
		timeObjects.clear();
	}

	long TimeManager::GetTime() const
	{
		return currentTime;
	}
}