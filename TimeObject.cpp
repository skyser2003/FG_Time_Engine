#include "stdafx.h"
#include "TimeObject.h"

namespace FG
{
	void TimeObject::TimeUpdate(int ms)
	{

	}

	void TimeObject::AddEntity(TimeEntity* entity)
	{
		timeEntities.push_back(entity);
	}
}