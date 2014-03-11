#pragma once

namespace CW
{
	class Position final
	{
	public:
		Position();
		Position(int x, int y);

		bool operator<(const Position& rhs) const;
		bool operator==(const Position& rhs) const;
		bool operator!=(const Position& rhs) const;

		void SetX(int x) { mX = x; }
		void SetY(int y) { mY = y; }
		void Set(int x, int y) { SetX(x); SetY(y); }

		int GetX() const { return mX; }
		int GetY() const { return mY; }
	private:
		int Hash() const;

		int mX, mY;
	};
}