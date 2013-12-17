#pragma once

#include "Mode.h"

namespace CW
{
	class GameMode : public Mode
	{
	public:
		GameMode();
		virtual ~GameMode();

		virtual void Initialize() override;
		virtual void Destroy() override;

		virtual void Run() override;
	private:
		virtual void Update(float dt) override;
		virtual void Draw(float dt) override;
	};
}