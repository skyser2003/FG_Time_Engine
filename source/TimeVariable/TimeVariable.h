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
		void SetToTime(long wantedTime) override
		{
			value = GetValue(wantedTime);
		}
		void SaveCurrentValue(long wantedTime) override
		{
			if(timeCapsule.size() == 0)
			{
				timeCapsule.insert(std::make_pair(wantedTime, value));
			}
			else if(value != timeCapsule.rbegin()->second)
			{
				timeCapsule.insert(std::make_pair(wantedTime, value));
			}
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

			// If wantedTime is later than last saved time
			if(timeCapsule.size() != 0)
			{
				return timeCapsule.rbegin()->second;
			}

			// If there is no value saved yet
			return value;
		}
		T GetCurrentValue() const
		{
			return value;
		}

		T& operator=(T value)
		{
			this->value = value;
			return this->value;
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