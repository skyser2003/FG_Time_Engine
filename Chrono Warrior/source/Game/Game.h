#pragma once

#include "Mode.h"

namespace FG
{
	class Window;
	class KeyboardInput;
}

class GraphicsClass;

namespace CW
{
	class Mode;

	class Game
	{
	public:
		void Initialize(_In_ HINSTANCE hInstance,
			_In_opt_ HINSTANCE hPrevInstance,
			_In_ LPTSTR    lpCmdLine,
			_In_ int       nCmdShow);
		void Destroy();

		void Run();
	private:
		std::shared_ptr<FG::Window> mWindow;
		std::shared_ptr<FG::KeyboardInput> mKeyboard;

		std::unique_ptr<Mode> mCurMode;
	};
}