#include "stdafx.h"
#include "Position.h"

namespace CW
{
	Position::Position() : Position(0, 0)
	{

	}
	Position::Position(int x, int y) : mX(x), mY(y)
	{

	}

	bool Position::operator<(const Position& rhs) const
	{
		return Hash() < rhs.Hash();
	}
	bool Position::operator==(const Position& rhs) const
	{
		return mX == rhs.mX && mY == rhs.mY;
	}
	bool Position::operator!=(const Position& rhs) const
	{
		return !operator==(rhs);
	}

	int Position::Hash() const
	{
		return 10000 * mX + mY;
	}
}