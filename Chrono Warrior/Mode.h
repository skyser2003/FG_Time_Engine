#pragma once

namespace CW
{
	class Mode
	{
	public:
		virtual ~Mode() = 0 {}

		virtual void Initialize();
		virtual void Destroy();

		virtual void Run() = 0;
	private:
	};
}