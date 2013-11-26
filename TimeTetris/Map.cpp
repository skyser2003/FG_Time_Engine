#include "stdafx.h"
#include "Map.h"

#include "Block.h"
#include "UtilFunc.h"
using namespace std;

Map::Map()
{
}
Map::~Map()
{
}

void Map::Initialize()
{
	Destroy();

	for(int i=0;i<10;++i)
	{
		for(int j=0;j<20;++j)
		{
			field[i][j] = 0;
		}
	}
}
void Map::Destroy()
{
}

Block* Map::CreateBlock()
{
	int type = rand() % 7;

	return CreateBlock(Block::Type(type));
}
Block* Map::CreateBlock(Block::Type type)
{
	Block* block = new Block(type);
	block->SetPosition(5,17);

	auto bodies = block->GetBodies();

	for(int i=0;i<4;++i)
	{
		if(field[bodies[i]->x][bodies[i]->y] != 0)
		{
			delete block;
			return nullptr;
		}
	}

	for(int i=0;i<4;++i)
	{
		field[bodies[i]->x][bodies[i]->y] = 1;
	}

	return block;
}

bool Map::Move(const std::array<FG::TimeVariable<Point>, 4>& oldBodies, const std::array<FG::TimeVariable<Point>, 4>& newBodies)
{
	for(int i=0;i<4;++i)
	{
		field[oldBodies[i]->x][oldBodies[i]->y] = 0;
	}

	bool moved = true;

	for(int i=0;i<4;++i)
	{
		// Edge check
		if(newBodies[i]->x < 0 || newBodies[i]->x > 9 || newBodies[i]->y < 0 || newBodies[i]->y > 19)
		{
			moved = false;
			break;
		}

		// Other block check
		if(field[newBodies[i]->x][newBodies[i]->y] != 0)
		{
			moved = false;
			break;
		}
	}

	if(moved == false)
	{
		for(int i=0;i<4;++i)
		{
			field[oldBodies[i]->x][oldBodies[i]->y] = 1;
		}
	}
	else
	{
		for(int i=0;i<4;++i)
		{
			field[newBodies[i]->x][newBodies[i]->y] = 1;
		}
	}

	return moved;
}

bool Map::IsFull(int y)
{
	bool isFull = true;

	for(int i=0;i<10;++i)
	{
		if(field[i][y] == 0)
		{
			isFull = false;
			break;
		}
	}

	return isFull;
}
void Map::ClearLine(int y)
{
	for(int i=0;i<10;++i)
	{
		field[i][y] = 0;
	}

	for(int i=0;i<10;++i)
	{
		for(int j = y;j<19;++j)
		{
			field[i][j] = field[i][j+1];
		}
	}
}
void Map::ClearLines()
{
	for(int i=0;i<20;++i)
	{
		if(IsFull(i))
		{
			ClearLine(i);
			--i;
		}
	}
}

std::array<std::array<int,20>, 10> Map::GetField() const
{
	return field;
}