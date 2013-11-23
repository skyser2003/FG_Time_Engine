#pragma once

#include <array>
#include <functional>
#include <vector>

#include "TimeVariable.h"
#include "Point.h"

class Map;
class Block;
class Point;

namespace FG
{
	class TimeManager;
}

class Game
{
private:
	enum BLOCK_MODE
	{
		BLOCK_START,

		BLOCK_NORMAL,
		BLOCK_REVERSE,

		BLOCK_END
	};
public:
	typedef bool (Game::*funcPointer)(void);
	Game();

	void Initialize();
	void Destroy();

	void Run();
private:
	template <int MODE, int END_MODE>
	void InitRunFunctions();

	template <int MODE>
	bool Run();
	void UpdateTimeManager(long pastTime, long currentTime);

	void BlockMoveDown();
	void BlockMoveUp();
	void BlockMoveLeft();
	void BlockMoveRight();
	void BlockMoveAllDown();

	void BlockRotateLeft();
	void BlockRotateRight();

	void BlockTimeSleep(unsigned long wantedTime);

	bool CreateNewBlock();
	void DeleteCurrentBlock();

	void Draw();

	Map* map;
	std::array<FG::TimeVariable<Point>, 4> oldBodies;
	Block* currentBlock;

	int past;
	int cooltime;
	
	FG::TimeManager* timeManager;
	BLOCK_MODE mode;

	std::vector<funcPointer> runFunctions;
};