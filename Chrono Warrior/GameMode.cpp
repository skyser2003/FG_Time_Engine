#include "stdafx.h"
#include "GameMode.h"

#include "Map.h"

#include "Window.h"
#include "KeyboardInput.h"
#include "MouseInput.h"

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

		mKeyboard.reset(new FG::KeyboardInput);
		mMouse.reset(new FG::MouseInput);

		window->RegisterInput(mKeyboard.get());
		window->RegisterInput(mMouse.get());

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
		// Keyboard input
		for (int keyCode : mKeyboard->GetDownKeys())
		{

		}

		// Mouse input
		FG::MouseInput::BUTTON_STATE lButton = mMouse->GetLButtonState();
		FG::MouseInput::BUTTON_STATE rButton = mMouse->GetRButtonState();
		float wheel = mMouse->GetWheelValue();

		if (lButton == FG::MouseInput::BUTTON_DOWN)
		{
		}

		// Map update
		mMap->ForeachTile([](Tile* tile)
		{
			
		});
		mMap->ForeachUnit([](FieldUnit* unit)
		{

		});
	}
}