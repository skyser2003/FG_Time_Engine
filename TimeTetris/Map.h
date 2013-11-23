#pragma once

#include "Block.h"

#include <array>
class Point;

class Map
{
public:
	Map();
	~Map();

	void Initialize();
	void Destroy();

	Block* CreateBlock();
	Block* CreateBlock(Block::Type type);

	bool Move(const std::array<FG::TimeVariable<Point>, 4>& oldBodies, const std::array<FG::TimeVariable<Point>, 4>& newBodies);

	bool IsFull(int y);
	void ClearLine(int y);
	void ClearLines();

	std::array<std::array<int,20>, 10> GetField() const;
private:
	std::array<std::array<int,20>, 10> field;
	// 0 : empty
	// 1 : block
};