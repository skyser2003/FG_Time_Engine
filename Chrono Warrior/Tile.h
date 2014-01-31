#pragma once

#include "Position.h"

namespace CW
{
	class FieldObject;
	class Tile
	{
	public:
		enum TileType
		{
			TILE_SPACE,
			TILE_ROAD
		};
	public:
		Tile();
		Tile(int x, int y);

		TileType GetType() const { return mType; }
		void SetType(TileType type) { mType = type; }

		void SetX(int x) { mPos.SetX(x); }
		void SetY(int y) { mPos.SetY(y); }
		void Set(int x, int y) { SetX(x); SetY(y); }

		int GetX() const { return mPos.GetX(); }
		int GetY() const { return mPos.GetY(); }
		Position GetPosition() const { return mPos; }
	private:
		TileType mType;
		Position mPos;
	};
}