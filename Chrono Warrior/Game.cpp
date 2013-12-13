#include "stdafx.h"
#include "Game.h"

#include "WindowManager.h"
#include "Window.h"
#include "KeyboardInput.h"

#include "GameMode.h"

namespace CW
{
	void Game::Initialize(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
	{
		// Graphics
		auto& wm = FG::WindowManager::GetInstance();
		wm.Initialize(hInstance, nCmdShow, hPrevInstance, lpCmdLine);

		mWindow = wm.CreateWindowInstance();
		mGraphics = &mWindow->GetGraphics();
		mKeyboard.reset(new FG::KeyboardInput);

		// Logic
		mCurMode.reset(new GameMode); // Later change to StartMenuMode
		mCurMode->Initialize();
	}
	void Game::Destroy()
	{
		// Logic
		mCurMode->Destroy();

		// Graphics
		FG::WindowManager::GetInstance().Destroy();
	}

	void Game::Run()
	{
		mCurMode->Run();
	}
}