#pragma once

#include "Mode.h"

namespace FG
{
	class DxCanvas;
	class VertexShader;
	class PixelShader;
	class TextureClass;
	class KeyboardInput;
	class MouseInput;
}

namespace CW
{
	class Map;
	class Tile;
	class FieldUnit;

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

		// Graphics
		virtual void Draw(std::chrono::system_clock::duration dt) override;

		void InitializeGraphics();

		void DrawTile(Tile* tile);
		void DrawUnit(FieldUnit* unit);

		std::chrono::system_clock::time_point currentTime;

		std::shared_ptr<Map> mMap;

		FG::DxCanvas* mCanvas;
		std::shared_ptr<FG::VertexShader> mVS;
		std::shared_ptr<FG::PixelShader> mPS;

		std::shared_ptr<FG::KeyboardInput> mKeyboard;
		std::shared_ptr<FG::MouseInput> mMouse;

		std::shared_ptr<FG::TextureClass> mLemon, mApple;
		std::shared_ptr<FG::TextureClass> mSoldier, mMage;
	};
}