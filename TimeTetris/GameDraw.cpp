#include "stdafx.h"
#include "Game.h"

#include "d3dclass.h"
#include "graphicsclass.h"
#include "textureclass.h"
#include "modelclass.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "TextureManager.h"

#include "WindowManager.h"
#include "Window.h"

#include "Map.h"

#include "TimeManager.h"
#include "UtilFunc.h"

#include "DxCanvas.h"

void Game::InitializeGraphics(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	HRESULT result;
	std::string vsFileName = "C:/Projects/Shaders/vstexture.hlsl";
	std::string psTextureFileName = "C:/Projects/Shaders/pstexture.hlsl";
	std::string psColorFileName = "C:/Projects/Shaders/pscolor.hlsl";

	FG::WindowManager::GetInstance().Initialize(hInstance, nCmdShow, hPrevInstance, lpCmdLine);
	mWindow = FG::WindowManager::GetInstance().CreateWindowInstance();

	mCanvas = &mWindow->GetCanvas();

	mVS = mCanvas->CreateVertexShader();
	mPSTexture = mCanvas->CreatePixelShader();
	mPSColor = mCanvas->CreatePixelShader();

	result = mVS->CompileShader(vsFileName.c_str(), "VertexTextureMain");
	if (FAILED(result))
	{
		MessageBox(mCanvas->GetGraphics()->GetHwnd(), "Error compiling shader.  Check shader-error.txt for message.", vsFileName.c_str(), MB_OK);
		return;
	}

	mVS->SetupShaderBufferInputType("POSITION");
	mVS->SetupShaderBufferInputType("COLOR");
	mVS->SetupShaderBufferInputType("TEXCOORD");
	mVS->CreateShaderBufferDesc();
	mVS->CreateCBufferDesc("matrix", sizeof(FG::MatrixBufferType));

	result = mPSTexture->CompileShader(psTextureFileName.c_str(), "PixelTextureMain");
	if (FAILED(result))
	{
		MessageBox(mCanvas->GetHwnd(), "Error compiling shader.  Check shader-error.txt for message.", psTextureFileName.c_str(), MB_OK);
		return;
	}

	mPSTexture->CreateSamplerState();

	result = mPSColor->CompileShader(psColorFileName.c_str(), "PixelColorMain");
	if (FAILED(result))
	{
		MessageBox(mCanvas->GetHwnd(), "Error compiling shader.  Check shader-error.txt for message.", psColorFileName.c_str(), MB_OK);
		return;
	}

	mPSColor->CreateSamplerState();

	mBlock.reset(new FG::TextureClass);
	mBlock->Initialize(mCanvas->GetDevice(), "C:/Projects/FGEngine/FG_Time_Engine/TimeTetris/square.jpg");

	mPSTexture->SetTexture(mBlock->GetTexture());
}
void Game::DestroyGraphics()
{
	delete mCanvas;
}

void Game::Draw()
{
	mCanvas->BeginRender();

	mCanvas->EquipVertexShader(mVS);
	mCanvas->EquipPixelShader(mPSColor);

	FG::MatrixBufferType matrixBuffer;
	D3DXMatrixTranspose(&matrixBuffer.world, &mCanvas->GetGraphics()->GetWorldMatrix());
	D3DXMatrixTranspose(&matrixBuffer.view, &mCanvas->GetGraphics()->GetViewMatrix());
	D3DXMatrixTranspose(&matrixBuffer.projection, &mCanvas->GetGraphics()->GetProjectionMatrix());

	mVS->SetCBufferDesc("matrix", &matrixBuffer, sizeof(matrixBuffer));

	auto field = map->GetField();
	for (int j = 0; j < 20; ++j)
	{
		D3DXVECTOR4 innerColor, outerColor;
		for (int i = 0; i < 10; ++i)
		{
			switch (field[i][j])
			{
			case 0: // empty
			{
				innerColor = { 1, 1, 1, 1 };
				outerColor = { 0, 0, 0, 1 };
			}
				break;
			case 1: // wall or block deposit
			{
				innerColor = { 0, 0, 0, 1 };
				outerColor = { 0.2f, 0.2f, 0.2f, 1 };
			}
				break;
			default:
			{

			}
				break;
			}

			DrawBlock(i, j, outerColor, innerColor);
		}
	}

	if (currentBlock != nullptr)
	{
		std::array<Point, 4> pastPoints;
		auto currentBodies = currentBlock->GetBodies();
		auto currentCenter = currentBlock->GetCenter();

		currentBlock->SetToTime(timeManager->GetTime() - 1000);

		auto pastBodies = currentBlock->GetBodies();

		for (unsigned i = 0; i < pastBodies.size(); ++i)
		{
			int x = pastBodies[i]->x;
			int y = pastBodies[i]->y;

			pastPoints[i] = Point(x, y);
		}

		currentBlock->SetBodies(currentCenter, currentBodies);

		// Past position
		mCanvas->EquipPixelShader(mPSTexture);
		for (int i = 0; i < 4; ++i)
		{
			int x = pastPoints[i].x;
			int y = pastPoints[i].y;
			DrawBlock(x, y, { 1, 1, 0, 1, }, { 1, 0, 0, 1 });
		}
		
		// Current position
		mCanvas->EquipPixelShader(mPSColor);
		for (int i = 0; i < 4; ++i)
		{
			DrawBlock(currentBodies[i]->x, currentBodies[i]->y, { 0.2f, 0.2f, 0.2f, 1 }, { 0, 0, 0, 1 });
		}
	}

	mCanvas->EndRender();
}

void Game::DrawBlock(int x, int y, D3DXVECTOR4 outerColor, D3DXVECTOR4 innerColor)
{
	int leftMargin = 50;
	int bottomMargin = 50;

	const int width = 25;
	const int height = 25;
	const int numVertices = 6;
	const float edgeRatio = 0.1f;

	FG::RenderInfo outerInfo, innerInfo;
	outerInfo.noVertices = numVertices;
	outerInfo.position.resize(numVertices);
	outerInfo.texPosition.resize(numVertices);

	innerInfo.noVertices = numVertices;
	innerInfo.position.resize(numVertices);
	innerInfo.texPosition.resize(numVertices);

	const D3DXVECTOR4 positions[numVertices] =
	{
		{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	const D3DXVECTOR2 texPositions[numVertices] =
	{
		{ 0, 1 },
		{ 0, 0 },
		{ 1, 0 },
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 }
	};

	D3DXVECTOR4 sqPosition[numVertices];
	
	// Outer square
	memcpy_s(sqPosition, sizeof(sqPosition), positions, sizeof(positions));

	for (int i = 0; i < numVertices; ++i)
	{
		sqPosition[i][0] += x;
		sqPosition[i][1] += y;

		sqPosition[i][0] *= width;
		sqPosition[i][1] *= height;

		sqPosition[i][0] += leftMargin;
		sqPosition[i][1] += bottomMargin;

		outerInfo.position[i] = sqPosition[i];
		outerInfo.texPosition[i] = texPositions[i];
	}

	outerInfo.color = outerColor;
	mCanvas->AddRenderInfo(outerInfo);

	// Inner square
	memcpy_s(sqPosition, sizeof(sqPosition), positions, sizeof(positions));

	for (int i = 0; i < numVertices; ++i)
	{
		sqPosition[i][0] += x;
		sqPosition[i][1] += y;

		sqPosition[i][0] *= width * (1.0f - edgeRatio);
		sqPosition[i][1] *= height * (1.0f - edgeRatio);

		sqPosition[i][0] += width * edgeRatio * (x + 0.5f);
		sqPosition[i][1] += height * edgeRatio * (y + 0.5f);

		sqPosition[i][0] += leftMargin;
		sqPosition[i][1] += bottomMargin;

		innerInfo.position[i] = sqPosition[i];
		innerInfo.texPosition[i] = texPositions[i];
	}

	innerInfo.color = innerColor;
	mCanvas->AddRenderInfo(innerInfo);
	mCanvas->Render();
}