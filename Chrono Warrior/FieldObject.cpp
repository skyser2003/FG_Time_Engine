#include "stdafx.h"
#include "FieldObject.h"

#include "Tile.h"

namespace CW
{
	FieldObject::~FieldObject()
	{

	}

	void FieldObject::Initialize()
	{

	}
	void FieldObject::Destroy()
	{

	}

	void FieldObject::SetTile(const std::shared_ptr<Tile>& tile)
	{
		mTile = tile;
	}

	int FieldObject::GetX() const
	{
		return mTile->GetX();
	}
	int FieldObject::GetY() const
	{
		return mTile->GetY();
	}
	Position FieldObject::GetPosition() const
	{
		return mTile->GetPosition();
	}
}