#pragma once

namespace FG
{
	class ITimeVariable
	{
	public:
		virtual void Update(int ms) = 0;
	private:
	};

	template <typename T, typename timeSize = unsigned long>
	class TimeVariable
	{
	public:
		TimeVariable() : latestValue(nullptr), variable(nullptr)
		{
		}

		void Update(timeSize currentTime) final
		{
			if(*variable != *latestValue)
			{
				timeCapsule.insert(std::make_pair(currentTime, *variable));
			}
		}

		void SetVariable(T variable)
		{
			this->variable = &variable;
		}
		void SetVariable(T* variable)
		{
			this->variable = variable;
		}
		
		T GetVariable()
		{
			return *variable;
		}
		T GetVariable(timeSize wantedTime)
		{
		}
	private:
		T* latestValue;
		T* variable;
		std::map<timeSize, T> timeCapsule;
	};
}