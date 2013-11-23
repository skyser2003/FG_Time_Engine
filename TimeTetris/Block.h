#pragma once

#include "Point.h"

#include "TimeObject.h"
#include "TimeVariable.h"

#include <array>

class Block : public FG::TimeObject
{
public:
	enum Type : int
	{
		I,
		J,
		L,
		O,
		S,
		T,
		Z
	};

	Block();
	Block(Type type);

	std::array<FG::TimeVariable<Point>, 4> MoveDown();
	std::array<FG::TimeVariable<Point>, 4> MoveUp();
	std::array<FG::TimeVariable<Point>, 4> MoveLeft();
	std::array<FG::TimeVariable<Point>, 4> MoveRight();

	std::array<FG::TimeVariable<Point>, 4> RotateLeft();
	std::array<FG::TimeVariable<Point>, 4> RotateRight();

	void SetPosition(Point center);
	void SetPosition(int x, int y);
	void SetBodies(Point center, std::array<FG::TimeVariable<Point>, 4> bodies);

	std::array<FG::TimeVariable<Point>, 4> GetBodies() const;
	Point GetCenter() const;
	Type GetType() const;

private:
	std::array<FG::TimeVariable<Point>, 4> Move(int dx, int dy);
	std::array<FG::TimeVariable<Point>, 4> Rotate(int times);

	void InitBodies(Type type);

	int Round(double f);
		
	Type type;

	std::array<FG::TimeVariable<Point>, 4> bodies;
	FG::TimeVariable<Point> center;
};