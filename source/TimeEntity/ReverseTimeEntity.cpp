#include "stdafx.h"
#include "ReverseTimeEntity.h"

#include "TimeObject/TimeObject.h"
#include "TimeVariable/ITimeVariable.h"

namespace FG
{
	ReverseTimeEntity::ReverseTimeEntity() : startTime(0), reverseTime(0)
	{

	}

	void ReverseTimeEntity::OnRegister(long currentTime, TimeObject* object)
	{
		startTime = reverseTime = currentTime;
	}
	void ReverseTimeEntity::OnUnregister(long currentTime, TimeObject* object)
	{

	}
	void ReverseTimeEntity::Update(long currentTime, TimeObject* object)
	{
		int diff = currentTime - startTime;
		reverseTime = startTime - diff;
		const auto timeVars = object->GetTimeVariables();

		for(auto* var : timeVars)
		{
			var->SetToTime(reverseTime);
			var->SaveCurrentValue(currentTime);
		}
	}
}