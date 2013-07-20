#pragma once

namespace FG
{
	class TimeObject;

	class TimeEntity
	{
	public:
		virtual ~TimeEntity() {}

		virtual void OnRegister(long currentTime, TimeObject* object) {};
		virtual void OnUnregister(long currentTime, TimeObject* object) {};
		virtual void Update(long currentTime, TimeObject* object) = 0;
	private:
	};
}