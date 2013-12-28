#include "stdafx.h"
#include "GameMode.h"

namespace CW
{
	GameMode::GameMode()
	{

	}
	GameMode::~GameMode()
	{

	}

	void GameMode::Initialize(const std::shared_ptr<FG::Window>& window)
	{
		Mode::Initialize(window);
		InitializeGraphics();
	}
	void GameMode::Destroy()
	{
		Mode::Destroy();
	}

	void GameMode::Run()
	{

	}

	void GameMode::Update(float dt)
	{

	}
}