#pragma once

#include "ITimeVariable.h"
#include <map>

namespace FG
{
	template <typename T>
	class TimeVariable final : public ITimeVariable
	{
	public:
		TimeVariable()
		{
		}
		TimeVariable(T value)
		{
			this->value = value;

			Update(0);
		}

		void Initialize()
		{
			timeCapsule.insert(std::make_pair(0, value));
		}
		void Destroy()
		{

		}
		void Update(unsigned long currentTime) override
		{
			if(timeCapsule.size() == 0)
			{
				timeCapsule.insert(std::make_pair(currentTime, value));
			}
			else if(value != timeCapsule.rbegin()->second)
			{
				timeCapsule.insert(std::make_pair(currentTime, value));
			}
		}

		T GetValue(unsigned long wantedTime)
		{
			if(timeCapsule.size() == 0)
			{
				return value;
			}
			else if(timeCapsule.size() == 1)
			{
				return timeCapsule.begin()->second;
			}

			for(std::pair<unsigned long, T> it : timeCapsule)
			{
				if(it.first < wantedTime)
				{
					
				}
			}

			// If no time has passed or wantedTime isn't valid
			return value;
		}

		void Set(T value)
		{
			this->value = value;
		}
		T Get()
		{
			return value;
		}

		operator T&()
		{
			return value;
		}
		operator const T&() const
		{
			return value;
		}
	private:
		T value;
		std::map<unsigned long, T> timeCapsule;
	};
}