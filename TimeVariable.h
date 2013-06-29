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

		T GetValue(long wantedTime)
		{
			if(timeCapsule.size() == 0)
			{
				return value;
			}
			else if(timeCapsule.size() == 1)
			{
				return timeCapsule.begin()->second;
			}

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
				//temp
				else if(it->first == wantedTime)
				{
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
	private:
		T value;
		std::map<long, T> timeCapsule;
	};
}