#include "Game.h"

#include "Map.h"
#include "Block.h"
#include "Point.h"

#include <Windows.h>
#include <conio.h>

#include "TimeManager.h"
#include "UtilFunc.h"

#include "NormalTimeEntity.h"
#include "ReverseTimeEntity.h"

#include <assert.h>

Game::Game()
{
	InitRunFunctions<BLOCK_START, BLOCK_END>();
}
template <int MODE, int END_MODE>
void Game::InitRunFunctions()
{
	runFunctions.push_back(&Game::Run<MODE>);

	InitRunFunctions<MODE+1, END_MODE>();
}

template <>
void Game::InitRunFunctions<Game::BLOCK_END, Game::BLOCK_END>()
{
}
void Game::Initialize()
{
	map = new Map;
	map->Initialize();

	currentBlock = nullptr;
	timeManager = new FG::TimeManager;

	past = 0;
	cooltime = 0;

	mode = BLOCK_NORMAL;

	srand(timeGetTime());
}
void Game::Destroy()
{
	DeleteCurrentBlock();

	map->Destroy();
	delete map;

	delete timeManager;
}

template <>
bool Game::Run<Game::BLOCK_START>()
{
	return false;
}
template <>
bool Game::Run<Game::BLOCK_NORMAL>()
{
	int keyInput;
	bool running = true;

	DWORD now = timeGetTime();
	int diff = now - past;
	past = now;
	cooltime -= diff;

	if(currentBlock == nullptr)
	{
		bool created = CreateNewBlock();

		if(!created)
			return false;
	}

	oldBodies = currentBlock->GetBodies();

	UpdateTimeManager(past, now);

	if(cooltime <= 0)
	{
		BlockMoveDown();
		Draw();
		cooltime = 1000;

		if(currentBlock == nullptr)
		{
			bool created = CreateNewBlock();

			if(!created)
				return false;
		}

		oldBodies = currentBlock->GetBodies();
	}

	if(_kbhit())
	{
		keyInput = _getch();
	}
	else
	{
		keyInput = -1;
	}

	switch(keyInput)
	{
	case 49: // 1
		{
			if(currentBlock)
			{
				currentBlock->UnregisterAllTimeEntities(timeManager->GetTime());
				currentBlock->RegisterTimeEntity(timeManager->GetTime(), new FG::NormalTimeEntity);

				mode = BLOCK_NORMAL;
			}
		}
		break;
	case 50: // 2
		{
			if(currentBlock)
			{
				currentBlock->UnregisterAllTimeEntities(timeManager->GetTime());
				currentBlock->RegisterTimeEntity(timeManager->GetTime(), new FG::ReverseTimeEntity);

				mode = BLOCK_REVERSE;
			}
		}
		break;
	case 51: // 3
		{

		}
		break;
	case 87: // w & W
	case 119:
		{
			BlockRotateRight();
		}
		break;
	case 65: // a & A
	case 97:
		{
			BlockMoveLeft();
		}
		break;
	case 68:
	case 100: // d & D
		{
			BlockMoveRight();
		}
		break;
	case 83: // s & S
	case 115:
		{
			BlockMoveDown();
		}
		break;
	case 0x20: // Space
		{
			BlockMoveAllDown();
		}
		break;
	case 81: // q & Q
	case 113:
		{
			running = false;
		}
		break;
	case 69: // e & E
	case 101:
		{
			BlockTimeSleep(timeManager->GetTime() - 1000);
		}
		break;
	case 70: // f & F
	case 102:
		{

		}
		break;
	case -1: // no key input
		{
			// nothing
		}
	default:
		{

		}
		break;
	}

	return running;
}
template <>
bool Game::Run<Game::BLOCK_REVERSE>()
{
	int keyInput;
	bool running = true;

	DWORD now = timeGetTime();
	int diff = now - past;
	past = now;

	UpdateTimeManager(past, now);

	if(_kbhit())
	{
		keyInput = _getch();
	}
	else
	{
		keyInput = -1;
	}

	switch(keyInput)
	{
	case 81: // q & Q
	case 113:
		{
			running = false;
		}
		break;
	case 49: // 1
		{
			if(currentBlock)
			{
				currentBlock->UnregisterAllTimeEntities(timeManager->GetTime());
				currentBlock->RegisterTimeEntity(timeManager->GetTime(), new FG::NormalTimeEntity);

				mode = BLOCK_NORMAL;
			}
		}
		break;
	case -1:
	default:
		{

		}
		break;
	}

	return running;
}
void Game::Run()
{
	bool running = true;
	int keyInput = -1;
	float drawCoolTime = 0.0f;

	past = timeGetTime();
	timeManager->StartTimer();

	while(running)
	{
		drawCoolTime -= (timeGetTime() - past);

		running = (this->*runFunctions[mode])();

		if(currentBlock && drawCoolTime <= 0.0f)
		{
			drawCoolTime = 60;
			Draw();
		}
	}

	timeManager->EndTimer();
}


void Game::UpdateTimeManager(long pastTime, long currentTime)
{
	timeManager->Update(currentTime);

	switch(mode)
	{
	case BLOCK_NORMAL:
		{

		}
		break;
	case BLOCK_REVERSE:
		{
			if(currentBlock) 
			{
				auto tempBody = currentBlock->GetBodies();
				map->Move(oldBodies, currentBlock->GetBodies());
				oldBodies = currentBlock->GetBodies();
			}
		}
		break;
	}
}

void Game::BlockMoveDown()
{
	auto bodies = currentBlock->MoveDown();
	bool moved = map->Move(oldBodies, bodies);

	if(!moved)
	{
		DeleteCurrentBlock();

		map->ClearLines();
	}
}
void Game::BlockMoveUp()
{

}
void Game::BlockMoveLeft()
{
	auto bodies = currentBlock->MoveLeft();
	bool moved = map->Move(oldBodies, bodies);

	if(!moved)
	{
		currentBlock->MoveRight();
	}
}
void Game::BlockMoveRight()
{
	auto bodies = currentBlock->MoveRight();
	bool moved = map->Move(oldBodies, bodies);

	if(!moved)
	{
		currentBlock->MoveLeft();
	}
}
void Game::BlockMoveAllDown()
{
	bool moved = true;
	auto tempOldBodies = oldBodies;

	do 
	{
		auto bodies = currentBlock->MoveDown();
		moved = map->Move(tempOldBodies, bodies);

		tempOldBodies = bodies;
	} while (moved);

	DeleteCurrentBlock();

	map->ClearLines();
}

void Game::BlockRotateLeft()
{
	auto bodies = currentBlock->RotateLeft();
	bool moved = map->Move(oldBodies, bodies);

	if(!moved)
	{
		currentBlock->RotateRight();
	}
}
void Game::BlockRotateRight()
{
	auto bodies = currentBlock->RotateRight();
	bool moved = map->Move(oldBodies, bodies);

	if(!moved)
	{
		currentBlock->RotateLeft();
	}
}

void Game::BlockTimeSleep(unsigned long wantedTime)
{
	if(currentBlock)
	{
		auto oldBodies = currentBlock->GetBodies();
		currentBlock->SetToTime(wantedTime);
		auto newBodies = currentBlock->GetBodies();

		map->Move(oldBodies, newBodies);
	}
}

bool Game::CreateNewBlock()
{
	DeleteCurrentBlock();

	currentBlock = map->CreateBlock();

	if(currentBlock == nullptr) // Dead!  Game end
	{
		return false;
	}

	timeManager->RegisterTimeObject(currentBlock);

	return true;
}
void Game::DeleteCurrentBlock()
{
	if(currentBlock)
	{
		delete currentBlock;
		timeManager->UnregisterTimeObject(currentBlock);
		currentBlock = nullptr;
	}
}

void Game::Draw()
{
	system("cls");

	auto field = map->GetField();

	std::array<Point, 4> pastPoints;

	if(currentBlock)
	{
		auto currentBodies = currentBlock->GetBodies();
		auto currentCenter = currentBlock->GetCenter();

		currentBlock->SetToTime(timeManager->GetTime() - 1000);
		auto pastBodies = currentBlock->GetBodies();

		for(unsigned i=0;i<pastBodies.size();++i)
		{
			int x = pastBodies[i]->x;
			int y = pastBodies[i]->y;

			pastPoints[i] = Point(x,y);
		}

		currentBlock->SetBodies(currentCenter, currentBodies);
	}

	for(int j=19;j>=0;--j)
	{
		printf("бс");

		for(int i=0;i<10;++i)
		{
			bool pastDrawn = false;

			for(Point past : pastPoints)
			{
				if(past.x == i && past.y == j && field[i][j] != 1)
				{
					color_printf(FOREGROUND_RED | FOREGROUND_INTENSITY, "бс");
					pastDrawn = true;
					break;
				}
			}

			if(pastDrawn)
			{
				continue;
			}

			switch(field[i][j])
			{
			case 0: // empty
				{
					printf_s("бр");
				}
				break;
			case 1: // block
				{
					color_printf(FOREGROUND_BLUE | FOREGROUND_INTENSITY, "бс");
				}
				break;
			default:
				{
					// error!
				}
				break;
			}
		}

		printf("бс");
		printf("\n");
	}

	for(int i=0;i<10 + 2;++i)
	{
		printf("бс");
	}

}