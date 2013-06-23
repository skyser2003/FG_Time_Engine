#pragma once

namespace FG
{
	class TimeObject;

	class TimeEntity
	{
	public:
		virtual void Update(int dt, TimeObject* object);
	private:
	};
}