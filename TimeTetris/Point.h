#pragma once

class Point
{
public:
	Point() : x(0), y(0)
	{
	}
	Point(int x, int y) : x(x), y(y)
	{
	}

	bool operator ==(const Point& rhs) const
	{
		if(x == rhs.x && y == rhs.y)
			return true;
		else
			return false;
	}
	bool operator !=(const Point& rhs) const
	{
		return !(*this == rhs);
	}

	int x, y;
};