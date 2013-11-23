#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

#include "Game.h"
#include "Map.h"
#include "Block.h"
#include "Point.h"

#include "TimeVariable.h"

using namespace FG;

int main()
{
	// Actual game
	Game game;

	game.Initialize();
	game.Run();
	game.Destroy();

	system("cls");
	printf("Game End!");

	system("pause");
	return 0;
}