#pragma once

namespace FG
{
	class Window;
	class KeyboardInput;
}

class GraphicsClass;

namespace CW
{
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
		GraphicsClass* mGraphics;
		std::shared_ptr<FG::KeyboardInput> mKeyboard;
	};
}