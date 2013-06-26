#pragma once

namespace FG
{
	class ITimeVariable
	{
	public:
		virtual void StartTimer() = 0;
		virtual void EndTimer() = 0;
		virtual void Update(unsigned long currentTime) = 0;
		virtual void SetToTime(unsigned long wantedTime) = 0;
	};
}