#pragma once

#include <fstream>
#include <map>

#include "ITimeVariable.h"

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
		}
		~TimeVariable()
		{
		}

		void StartTimer(long startTime) override
		{
			timeCapsule.insert(std::make_pair(startTime, value));
		}
		void EndTimer() override
		{

		}
		void Update(long currentTime) override
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
		void SetToTime(long wantedTime)
		{
			value = GetValue(wantedTime);
		}

		T GetValue(long wantedTime) const
		{
			for(auto it = timeCapsule.begin(); it != timeCapsule.end(); ++it)
			{
				if(it->first > wantedTime)
				{
					if(it != timeCapsule.begin())
					{
						--it;
					}

					return it->second;
				}
			}

			// If no time has passed or wantedTime isn't valid
			return value;
		}

		T& operator*()
		{
			return value;
		}
		const T& operator*() const
		{
			return value;
		}

		T* operator->()
		{
			return &value;
		}
		const T* operator->() const
		{
			return &value;
		}

		bool operator==(const TimeVariable<T>& rhs) const
		{
			return value == rhs.value;
		}
		bool operator!=(const TimeVariable<T>& rhs) const
		{
			return !((*this) == rhs);
		}
	private:
		T value;
		std::map<long, T> timeCapsule;
	};
}