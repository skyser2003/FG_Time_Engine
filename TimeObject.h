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

		virtual void StartTimer(unsigned long startTime);
		virtual void EndTimer();
		void Update(unsigned long currentTime);

		void SetToTime(unsigned long wantedTime);

		void AddEntity(TimeEntity* entity);

		void RegisterTimeVariable(ITimeVariable* variable);
		void UnRegisterTimeVariable(ITimeVariable* variable);

		const std::vector<ITimeVariable*> GetTimeVariables() const;
		int GetStartTime() const;
	private:
		std::vector<TimeEntity*> timeEntities;
		std::vector<ITimeVariable*> timeVariables;

		unsigned long startTime;
		bool paused;
	};
}