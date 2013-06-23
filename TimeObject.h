#pragma once

#include <vector>

namespace FG
{
	class TimeEntity;
	class ITimeVariable;

	class TimeObject
	{
	public:
		virtual ~TimeObject();

		void Update(unsigned long currentTime);

		void AddEntity(TimeEntity* entity);

		void RegisterTimeVariable(ITimeVariable* variable);
		void UnRegisterTimeVariable(ITimeVariable* variable);

		const std::vector<ITimeVariable*> GetTimeVariables() const;
	private:
		std::vector<TimeEntity*> timeEntities;
		std::vector<ITimeVariable*> timeVariables;
	};
}