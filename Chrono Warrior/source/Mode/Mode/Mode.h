#pragma once

namespace FG
{
	class Window;
};

namespace CW
{
	class Mode
	{
	public:
		virtual ~Mode() = 0 {}

		virtual void Initialize(const std::shared_ptr<FG::Window>& window);
		virtual void Destroy();

		virtual bool Run() = 0;

		std::shared_ptr<FG::Window> GetWindow() const { return mWindow; }
	private:
		virtual void Update(std::chrono::system_clock::duration dt) = 0;
		virtual void Draw(std::chrono::system_clock::duration dt) = 0;

		std::shared_ptr<FG::Window> mWindow;
	};
}