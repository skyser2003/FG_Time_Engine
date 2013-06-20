#pragma once

#include <map>

namespace FG
{
	class ITimeVariable
	{
	public:
		virtual void Update(int ms) = 0;
	private:
	};

	template <typename T, typename timeSize = unsigned long>
	class TimeVariable final
	{
	public:
		TimeVariable() : latestValue(nullptr)
		{
		}

		void Update(timeSize currentTime)
		{
			if(variable != *latestValue)
			{
				timeCapsule.insert(std::make_pair(currentTime, variable));
			}
		}
		T GetValue(timeSize wantedTime)
		{
			if(timeCapsule.size() == 0)
			{
				return variable;
			}
			else if(timeCapsule.size() == 1)
			{

			}

			auto itNext = timeCapsule.begin();
			++itNext;

			for(auto it : timeCapsule)
			{

			}

			// If no time has passed or wantedTime isn't valid
			return variable;
		}

		operator T&()
		{
			return variable;
		}
		operator const T&() const
		{
			return variable;
		}

	private:
		T* latestValue;
		T variable;
		std::map<timeSize, T> timeCapsule;
	};
}