#pragma once

#include "FieldObject.h"

namespace CW
{
	class FieldUnit : public FieldObject
	{
	public:
		virtual ~FieldUnit();

		virtual void Initialize();
		virtual void Destroy();
	private:
	};
}