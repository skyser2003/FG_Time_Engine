#pragma once

#include "Position.h"

namespace CW
{
	class FieldObject;
	class Tile
	{
	public:
		Tile();
		Tile(int x, int y);

		void SetX(int x) { mPos.SetX(x); }
		void SetY(int y) { mPos.SetY(y); }
		void Set(int x, int y) { SetX(x); SetY(y); }

		int GetX() const { return mPos.GetX(); }
		int GetY() const { return mPos.GetY(); }
	private:
		Position mPos;
	};
}