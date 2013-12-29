#include "stdafx.h"
#include "GameMode.h"

#include "Map.h"

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

		mMap.reset(new Map);
		mMap->Initialize();
		currentTime = std::chrono::system_clock::now();

		InitializeGraphics();
	}
	void GameMode::Destroy()
	{
		Mode::Destroy();
	}

	void GameMode::Run()
	{
		auto now = std::chrono::system_clock::now();
		auto duration = now - currentTime;
		currentTime = now;

		Update(duration);
		Draw(duration);
	}

	void GameMode::Update(std::chrono::system_clock::duration dt)
	{

	}
}