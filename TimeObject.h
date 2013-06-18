#pragma once

namespace FG
{
	class TimeEntity;
	class TimeObject
	{
	public:
		void TimeUpdate(int ms);

		void AddEntity(TimeEntity* entity);
	private:
		std::vector<TimeEntity*> timeEntities;
	};
}