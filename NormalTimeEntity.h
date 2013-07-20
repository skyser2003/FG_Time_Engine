#pragma once

#include "TimeEntity.h"

namespace FG
{
	class NormalTimeEntity : public TimeEntity
	{
	public:
		virtual void Update(long currentTime, TimeObject* object) override;
	};
}