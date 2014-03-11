#pragma once

#include "Mode.h"
#include "Position.h"

namespace FG
{
	class DxCanvas;
	class VertexShader;
	class PixelShader;
	class TextureClass;
	class KeyboardInput;
	class MouseInput;

	class UIManager;
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

		virtual bool Run() override;
	private:
		// Logic
		virtual void Update(std::chrono::system_clock::duration dt) override;

		// Graphics
		virtual void Draw(std::chrono::system_clock::duration dt) override;

		void InitializeGraphics();

		void DrawTile(Tile* tile);
		void DrawUnit(FieldUnit* unit);

		int GetTileX(WORD screenX) const;
		int GetTileY(WORD screenY) const;
		Position GetTilePosition(WORD screenX, WORD screenY) const;

		// Logic variables
		std::chrono::system_clock::time_point currentTime;
		std::shared_ptr<Map> mMap;
		std::shared_ptr<FieldUnit> mSelectedUnit;

		// UI variables
		FG::UIManager* mUIM;

		// Graphics variables
		FG::DxCanvas* mCanvas;
		std::shared_ptr<FG::VertexShader> mVS;
		std::shared_ptr<FG::PixelShader> mPS;

		std::shared_ptr<FG::KeyboardInput> mKeyboard;
		std::shared_ptr<FG::MouseInput> mMouse;

		std::shared_ptr<FG::TextureClass> mLemon, mApple;
		std::shared_ptr<FG::TextureClass> mSoldier, mMage;

		// Canvas
		const int mTileWidth = 50;
		const int mTileHeight = 50;
		int mLeftMargin = 50;
		int mBottomMargin = 50;
	};
}