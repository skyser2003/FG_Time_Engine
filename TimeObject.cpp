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
		for(auto it : timeEntities)
		{
			delete it;
		}
	}

	void TimeObject::StartTimer(unsigned long startTime)
	{
		this->startTime = startTime;

		for(auto var : timeVariables)
		{
			var->StartTimer();
		}
	}
	void TimeObject::EndTimer()
	{
		for(auto var : timeVariables)
		{
			var->EndTimer();
		}
	}
	void TimeObject::Update(unsigned long currentTime)
	{
		currentTime -= startTime;

		if(currentTime < 0)
			currentTime = 0;

		for(auto var : timeVariables)
		{
			var->Update(currentTime);
		}
	}

	void TimeObject::SetToTime(unsigned long wantedTime)
	{
		for(auto var : timeVariables)
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
	int TimeObject::GetStartTime() const
	{
		return startTime;
	}
}