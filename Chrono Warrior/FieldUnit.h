#pragma once

#include "FieldObject.h"

namespace CW
{
	class FieldUnit : public FieldObject
	{
	public:
		enum FIELDUNIT_TYPE
		{
			FU_DEFAULT,
			FU_CHRONO_MAGE,
			FU_CHRONO_SOLDIER
		};
	public:
		virtual ~FieldUnit();

		virtual void Initialize();
		virtual void Destroy();

		void SetUnitType(FIELDUNIT_TYPE type) { mType = type; }
		FIELDUNIT_TYPE GetUnitTYpe() const { return mType; }
	private:
		FIELDUNIT_TYPE mType;
	};
}