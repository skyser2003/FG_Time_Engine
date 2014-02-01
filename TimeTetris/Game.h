#pragma once

#include <array>
#include <functional>
#include <vector>

#include "TimeVariable.h"
#include "Point.h"

class Map;
class Block;
class Point;

namespace FG
{
	class DxCanvas;
	class GraphicsClass;
	class TextureClass;
	class VertexShader;
	class PixelShader;
	class ModelClass;

	class TimeManager;
	class Window;
	class KeyboardInput;
}

class Game
{
private:
	enum BLOCK_MODE
	{
		BLOCK_START,

		BLOCK_NORMAL,
		BLOCK_REVERSE,

		BLOCK_END
	};
public:
	typedef bool (Game::*funcPointer)(void);
	Game();

	void Initialize(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPTSTR    lpCmdLine,
		_In_ int       nCmdShow);
	void Destroy();

	void Run();
private:
	template <int MODE>
	void InitRunFunctions();
	void InitializeGraphics(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPTSTR    lpCmdLine,
		_In_ int       nCmdShow);
	void DestroyGraphics();

	template <int MODE>
	bool Run();
	void UpdateTimeManager(long pastTime, long currentTime);

	void BlockMoveDown();
	void BlockMoveUp();
	void BlockMoveLeft();
	void BlockMoveRight();
	void BlockMoveAllDown();

	void BlockRotateLeft();
	void BlockRotateRight();

	void BlockTimeSleep(unsigned long wantedTime);

	bool CreateNewBlock();
	void DeleteCurrentBlock();

	void Draw();
	void DrawBlock(int x, int y, D3DXVECTOR4 outerColo, D3DXVECTOR4 innerColor);

	Map* map;
	std::array<FG::TimeVariable<Point>, 4> oldBodies;
	Block* currentBlock;

	int past;
	int cooltime;
	
	FG::TimeManager* timeManager;
	BLOCK_MODE mode;

	std::vector<funcPointer> runFunctions;

	// Graphis
	std::shared_ptr<FG::Window> mWindow;
	FG::DxCanvas* mCanvas;
	std::shared_ptr<FG::VertexShader> mVS;
	std::shared_ptr<FG::PixelShader> mPSTexture, mPSColor;
	std::shared_ptr<FG::TextureClass> mBlock;

	FG::KeyboardInput* mKeyboard;
};