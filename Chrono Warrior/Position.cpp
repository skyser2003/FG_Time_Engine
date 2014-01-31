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

	int Position::Hash() const
	{
		return 10000 * mX + mY;
	}
}