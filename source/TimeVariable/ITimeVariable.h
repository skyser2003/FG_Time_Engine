#pragma once

namespace FG
{
	class ITimeVariable
	{
	public:
		virtual void StartTimer(long startTime) = 0;
		virtual void EndTimer() = 0;
		virtual void SetToTime(long wantedTime) = 0;
		virtual void SaveCurrentValue(long wantedTime) = 0;
	};
}