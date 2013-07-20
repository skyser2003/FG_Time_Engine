#pragma once

#include <vector>
#include <fstream>

namespace FG
{
	class TimeObject;

	class TimeManager final
	{
	public:
		TimeManager();

		void StartTimer();
		void EndTimer();
		void Update(long currentTime);

		void RegisterTimeObject(TimeObject* object);
		void UnregisterTimeObject(TimeObject* object);
		void ClearTimeObjects();

		long GetTime() const;
	private:
		long currentTime;
		int dt;
		std::vector<TimeObject*> timeObjects;
	};
}