#include "Block.h"

#include <cmath>
#include <random>

#define M_PI       3.14159265358979323846

Block::Block() : type(Type(rand() % 7))
{
	InitBodies(type);
}
Block::Block(Type type) : type(type)
{
	InitBodies(type);
}

std::array<FG::TimeVariable<Point>, 4> Block::MoveDown()
{
	return Move(0, -1);
}
std::array<FG::TimeVariable<Point>, 4> Block::MoveUp()
{
	return Move(0, 1);
}
std::array<FG::TimeVariable<Point>, 4> Block::MoveLeft()
{
	return Move(-1, 0);
}
std::array<FG::TimeVariable<Point>, 4> Block::MoveRight()
{
	return Move(1, 0);
}

std::array<FG::TimeVariable<Point>, 4> Block::RotateLeft()
{
	return Rotate(1);
}
std::array<FG::TimeVariable<Point>, 4> Block::RotateRight()
{
	return Rotate(-1);
}

void Block::SetPosition(Point center)
{
	Point diff = Point(center.x - this->center->x, center.y - this->center->y);
	this->center = center;

	for(auto& pt : bodies)
	{
		pt->x += diff.x;
		pt->y += diff.y;
	}
}
void Block::SetPosition(int x, int y)
{
	SetPosition(Point(x,y));
}
void Block::SetBodies(Point center, std::array<FG::TimeVariable<Point>, 4> bodies)
{
	this->center = center;
	this->bodies = bodies;
}

std::array<FG::TimeVariable<Point>, 4> Block::GetBodies() const
{
	return bodies;
}
Point Block::GetCenter() const
{
	return *center;
}
Block::Type Block::GetType() const
{
	return type;
}

std::array<FG::TimeVariable<Point>, 4> Block::Move(int dx, int dy)
{
	for(auto& pt : bodies)
	{
		pt->x += dx;
		pt->y += dy;
	}

	center->x += dx;
	center->y += dy;

	return bodies;
}
std::array<FG::TimeVariable<Point>, 4> Block::Rotate(int times)
{
 	double radian =  (90.0f * times * M_PI) / 180.0f;

	for(auto& pt : bodies)
	{
		switch(GetType())
		{
		case O:
			{
				// no rotation
			}
			break;
		case I:
		case J:
		case L:
		case T:
		default:
			{
				int relativeX = pt->x - center->x;
				int relativeY = pt->y - center->y;

				pt->x = center->x + Round(relativeX * cos(radian) - relativeY * sin(radian));
				pt->y = center->y + Round(relativeX * sin(radian) + relativeY * cos(radian));
			}
		}
	}

	return bodies;
}
void Block::InitBodies(Type type = I)
{
	RegisterTimeVariable(&center);

	for(int i=0;i<4;++i)
	{
		RegisterTimeVariable(&bodies[i]);
	}

	center = Point(1,1);

	switch(type)
	{
	case J:
		{
			bodies[0] = Point(0,1);
			bodies[1] = Point(1,1);
			bodies[2] = Point(2,1);
			bodies[3] = Point(2,0);
		}
		break;
	case L:
		{
			bodies[0] = Point(0,0);
			bodies[1] = Point(0,1);
			bodies[2] = Point(1,1);
			bodies[3] = Point(2,1);
		}
		break;
	case O:
		{
			bodies[0] = Point(0,0);
			bodies[1] = Point(0,1);
			bodies[2] = Point(1,1);
			bodies[3] = Point(1,0);
		}
		break;
	case S:
		{
			bodies[0] = Point(0,0);
			bodies[1] = Point(1,0);
			bodies[2] = Point(1,1);
			bodies[3] = Point(2,1);
		}
		break;
	case T:
		{
			bodies[0] = Point(0,1);
			bodies[1] = Point(1,1);
			bodies[2] = Point(2,1);
			bodies[3] = Point(1,2);
		}
		break;
	case Z:
		{
			bodies[0] = Point(0,1);
			bodies[1] = Point(1,1);
			bodies[2] = Point(1,0);
			bodies[3] = Point(2,0);
		}
		break;
	case I:
	default:
		{
			bodies[0] = Point(1,0);
			bodies[1] = Point(1,1);
			bodies[2] = Point(1,2);
			bodies[3] = Point(1,3);
		}
		break;
	}
}

int Block::Round(double f)
{
	double intpart;
	int sign = f >= 0.0f ? 1 : -1;

	double copy = modf(abs(f), &intpart);

	if(copy >= 0.5f)
		return sign * (int)ceil(abs(f));
	else
		return sign * (int)floor(abs(f));
}