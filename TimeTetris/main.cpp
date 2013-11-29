#include "stdafx.h"

#include "Game.h"
#include "Map.h"
#include "Block.h"
#include "Point.h"

#include "TimeVariable.h"

using namespace FG;

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// Actual game
	Game game;

	game.Initialize(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	game.Run();
	game.Destroy();

	return 0;
}