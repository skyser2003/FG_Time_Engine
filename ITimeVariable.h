#pragma once

namespace FG
{
	class ITimeVariable
	{
	public:
		virtual void StartTimer(long startTime) = 0;
		virtual void EndTimer() = 0;
		virtual void Update(long currentTime) = 0;
		virtual void SetToTime(long wantedTime) = 0;
	};
}