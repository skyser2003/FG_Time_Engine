#pragma once

#include "TimeEntity.h"

namespace FG
{
	class ReverseTimeEntity : public TimeEntity
	{
	public:
		ReverseTimeEntity();

		virtual void OnRegister(long currentTime, TimeObject* object) override;
		virtual void OnUnregister(long currentTime, TimeObject* object) override;
		virtual void Update(long currentTime, TimeObject* object) override;
	private:
		long startTime;
		long reverseTime;
	};
}