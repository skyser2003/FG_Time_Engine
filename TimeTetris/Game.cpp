#include "stdafx.h"
#include "Game.h"

#include "Map.h"
#include "Block.h"
#include "Point.h"

#include "TimeManager.h"
#include "KeyboardInput.h"

#include "NormalTimeEntity.h"
#include "ReverseTimeEntity.h"
#include "Window.h"

Game::Game()
{
	InitRunFunctions<BLOCK_START>();
}
template <int MODE>
void Game::InitRunFunctions()
{
	runFunctions.push_back(&Game::Run<MODE>);

	InitRunFunctions<MODE+1>();
}

template <>
void Game::InitRunFunctions<Game::BLOCK_END>()
{
}
void Game::Initialize(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)

{
	InitializeGraphics(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	mKeyboard = new FG::KeyboardInput;
	mWindow->RegisterInput(mKeyboard);

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

	DestroyGraphics();
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

	past = timeGetTime();
	timeManager->StartTimer();

	MSG msg;

	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Draw();
		running = (this->*runFunctions[mode])();
	} while (running && msg.message != WM_QUIT);

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