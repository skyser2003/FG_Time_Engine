#include "stdafx.h"
#include "NormalTimeEntity.h"

#include "TimeObject.h"
#include "ITimeVariable.h"

namespace FG
{
	void NormalTimeEntity::Update(long currentTime, TimeObject* object)
	{
		const auto timeVars = object->GetTimeVariables();

		for(auto* var : timeVars)
		{
			var->SaveCurrentValue(currentTime);
		}
	}
}