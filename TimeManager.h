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
		void Update(int dt);

		void RegisterTimeObject(TimeObject* object);
		void UnregisterTimeObject(TimeObject* object);
		void ClearTimeObjects();

		long GetTime() const;
	private:
		long currentTime;
		std::vector<TimeObject*> timeObjects;
	};
}