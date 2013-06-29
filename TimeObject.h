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

		void AddEntity(TimeEntity* entity);

		void RegisterTimeVariable(ITimeVariable* variable);
		void UnRegisterTimeVariable(ITimeVariable* variable);

		const std::vector<ITimeVariable*> GetTimeVariables() const;
	private:
		std::vector<TimeEntity*> timeEntities;
		std::vector<ITimeVariable*> timeVariables;

		bool paused;
	};
}