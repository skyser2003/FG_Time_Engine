#pragma once

#include "FieldObject.h"

namespace CW
{
	enum FIELDUNIT_TYPE
	{
		FU_DEFAULT,
		FU_CHRONO_MAGE,
		FU_CHRONO_SOLDIER
	};

	class FieldUnit : public FieldObject
	{
	public:
		virtual ~FieldUnit();

		virtual void Initialize();
		virtual void Destroy();

		void SetUnitType(FIELDUNIT_TYPE type) { mType = type; }
	private:
		FIELDUNIT_TYPE mType;
	};
}