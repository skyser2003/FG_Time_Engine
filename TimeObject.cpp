#include "stdafx.h"
#include "TimeObject.h"

#include "TimeEntity.h"
#include "ITimeVariable.h"

namespace FG
{
	TimeObject::TimeObject() : paused(false), startTime(0)
	{

	}
	TimeObject::~TimeObject()
	{
		for(auto* it : timeEntities)
		{
			delete it;
		}
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
		for(ITimeVariable* var : timeVariables)
		{
			var->Update(currentTime);
		}
	}

	void TimeObject::SetToTime(long wantedTime)
	{
		for(ITimeVariable* var : timeVariables)
		{
			var->SetToTime(wantedTime);
		}
	}

	void TimeObject::AddEntity(TimeEntity* entity)
	{
		timeEntities.push_back(entity);
	}

	void TimeObject::RegisterTimeVariable(ITimeVariable* variable)
	{
		timeVariables.push_back(variable);
	}
	void TimeObject::UnRegisterTimeVariable(ITimeVariable* variable)
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

	const std::vector<ITimeVariable*> TimeObject::GetTimeVariables() const
	{
		return timeVariables;
	}
	long TimeObject::GetStartTime() const
	{
		return startTime;
	}
}