#pragma once

#include <vector>

namespace FG
{
	class TimeEntity;

	class TimeObject
	{
	public:
		virtual ~TimeObject();

		void Update(int ms);

		void AddEntity(TimeEntity* entity);
	private:
		std::vector<TimeEntity*> timeEntities;
	};
}