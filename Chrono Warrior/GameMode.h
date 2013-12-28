#pragma once

#include "Mode.h"

class DxCanvas;
class VertexShader;
class PixelShader;

namespace CW
{
	class Map;

	class GameMode : public Mode
	{
	public:
		GameMode();
		virtual ~GameMode();

		virtual void Initialize(const std::shared_ptr<FG::Window>& window) override;
		virtual void Destroy() override;

		virtual void Run() override;
	private:
		// Logic
		virtual void Update(float dt) override;

		std::shared_ptr<Map> mMap;

		// Graphics
		virtual void Draw(float dt) override;

		void InitializeGraphics();

		DxCanvas* mCanvas;
		std::shared_ptr<VertexShader> mVS;
		std::shared_ptr<PixelShader> mPS;
	};
}