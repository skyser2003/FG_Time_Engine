#include "stdafx.h"
#include "TimeObject.h"

#include "TimeEntity.h"
#include "ITimeVariable.h"

namespace FG
{
	TimeObject::~TimeObject()
	{
		for(auto it : timeEntities)
		{
			delete it;
		}
	}

	void TimeObject::Update(unsigned long currentTime)
	{
		for(auto var : timeVariables)
		{
			var->Update(currentTime);
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

}