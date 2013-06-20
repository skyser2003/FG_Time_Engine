#include "stdafx.h"
#include "TimeObject.h"

#include "TimeEntity.h"

namespace FG
{
	TimeObject::~TimeObject()
	{
		for(auto it : timeEntities)
		{
			delete it;
		}
	}

	void TimeObject::Update(int ms)
	{

	}

	void TimeObject::AddEntity(TimeEntity* entity)
	{
		timeEntities.push_back(entity);
	}
}