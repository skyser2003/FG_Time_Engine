#pragma once

#include <vector>

namespace FG
{
	class TimeEntity;
	class ITimeVariable;

	class TimeObject
	{
	public:
		TimeObject();
		virtual ~TimeObject();

		virtual void StartTimer(long startTime);
		virtual void EndTimer();
		void Update(long currentTime);

		void SetToTime(long wantedTime);

		void RegisterTimeEntity(long currentTime, TimeEntity* entity);
		void UnregisterTimeEntity(long currentTime, TimeEntity* entity);
		void UnregisterAllTimeEntities(long currentTime);

		void RegisterTimeVariable(ITimeVariable* variable);
		void UnregisterTimeVariable(ITimeVariable* variable);
		void UnregisterAllTimeVariables();

		const std::vector<ITimeVariable*> GetTimeVariables() const;
		long GetStartTime() const;
	private:
		std::vector<TimeEntity*> timeEntities;
		std::vector<ITimeVariable*> timeVariables;

		bool paused;
		long startTime;
	};
}