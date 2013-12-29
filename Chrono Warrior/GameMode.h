#pragma once

#include "Mode.h"

class DxCanvas;
class VertexShader;
class PixelShader;
class TextureClass;

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
		virtual void Update(std::chrono::system_clock::duration dt) override;

		std::shared_ptr<Map> mMap;

		// Graphics
		virtual void Draw(std::chrono::system_clock::duration dt) override;

		void InitializeGraphics();

		std::chrono::system_clock::time_point currentTime;

		DxCanvas* mCanvas;
		std::shared_ptr<VertexShader> mVS;
		std::shared_ptr<PixelShader> mPS;
		std::shared_ptr<TextureClass> mTx;
	};
}