#include "stdafx.h"
#include "TimeObject.h"

#include "TimeEntity/TimeEntity.h"
#include "TimeVariable/ITimeVariable.h"

#include "TimeEntity/NormalTimeEntity.h"

namespace FG
{
	TimeObject::TimeObject() : paused(false), startTime(0)
	{
		timeEntities.push_back(new NormalTimeEntity);
	}
	TimeObject::~TimeObject()
	{
		for(auto* it : timeEntities)
		{
			delete it;
		}

		timeEntities.clear();
	}

	void TimeObject::StartTimer(long startTime)
	{
		this->startTime = startTime;

		for(ITimeVariable* var : timeVariables)
		{
			var->StartTimer(startTime);
		}
	}
	void TimeObject::EndTimer()
	{
		for(ITimeVariable* var : timeVariables)
		{
			var->EndTimer();
		}
	}
	void TimeObject::Update(long currentTime)
	{
		for(TimeEntity* entity : timeEntities)
		{
			entity->Update(currentTime, this);
		}
	}

	void TimeObject::SetToTime(long wantedTime)
	{
		for(ITimeVariable* var : timeVariables)
		{
			var->SetToTime(wantedTime);
		}
	}

	void TimeObject::RegisterTimeEntity(long currentTime, TimeEntity* entity)
	{
		entity->OnRegister(currentTime, this);
		timeEntities.push_back(entity);
	}
	void TimeObject::UnregisterTimeEntity(long currentTime, TimeEntity* entity)
	{
		for(auto it = timeEntities.begin(); it != timeEntities.end(); ++it)
		{
			if(*it == entity)
			{
				entity->OnUnregister(currentTime, this);
				timeEntities.erase(it);
				return;
			}
		}
	}
	void TimeObject::UnregisterAllTimeEntities(long currentTime)
	{
		for(auto* entity : timeEntities)
		{
			entity->OnUnregister(currentTime, this);
			delete entity;
		}

		timeEntities.clear();
	}

	void TimeObject::RegisterTimeVariable(ITimeVariable* variable)
	{
		timeVariables.push_back(variable);
	}
	void TimeObject::UnregisterTimeVariable(ITimeVariable* variable)
	{
		for(auto it = timeVariables.begin(); it != timeVariables.end(); ++it)
		{
			if(*it == variable)
			{
				timeVariables.erase(it);
				return;
			}
		}
	}
	void TimeObject::UnregisterAllTimeVariables()
	{
		timeVariables.clear();
	}

	const std::vector<ITimeVariable*> TimeObject::GetTimeVariables() const
	{
		return timeVariables;
	}
	long TimeObject::GetStartTime() const
	{
		return startTime;
	}
}