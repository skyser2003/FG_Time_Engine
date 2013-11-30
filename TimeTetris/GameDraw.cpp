#include "stdafx.h"
#include "Game.h"

#include "d3dclass.h"
#include "graphicsclass.h"
#include "textureclass.h"
#include "modelclass.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "WindowManager.h"
#include "Window.h"

#include "Map.h"

#include "TimeManager.h"
#include "UtilFunc.h"

void Game::InitializeGraphics(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	FG::WindowManager::GetInstance().Initialize(hInstance, nCmdShow, hPrevInstance, lpCmdLine);
	mWindow = FG::WindowManager::GetInstance().CreateWindowInstance();
	mGraphics = &mWindow->GetGraphics();

	mVS = new VertexShader;
	mPS = new PixelShader;
	mModel = new ModelClass;
	mTexture = new TextureClass;

	mGraphics->Initialize(800, 600, mWindow->GetHwnd());
	mVS->Initialize();
	mVS->SetDevice(mGraphics->GetDevice());
	mVS->SetDeviceContext(mGraphics->GetDeviceContext());
	mVS->CompileShader("C:/Projects/Shaders/vstexture.hlsl", "TextureVertexShader");

	mVS->SetupShaderBufferInputType("POSITION");
	mVS->SetupShaderBufferInputType("TEXCOORD");
	mVS->SetupShaderBufferInputType("COLOR");
	mVS->CreateShaderBufferDesc();
	mVS->CreateCBufferDesc("matrix", sizeof(MatrixBufferType));

	mPS->Initialize();
	mPS->SetDevice(mGraphics->GetDevice());
	mPS->SetDeviceContext(mGraphics->GetDeviceContext());
	mPS->CompileShader("C:/Projects/Shaders/pscolor.hlsl", "ColorPixelShader");
	mPS->CreateSamplerState();

	mVS->EquipShader();
	mPS->EquipShader();
}
void Game::DestroyGraphics()
{
	mVS->Destroy();
	mPS->Destroy();
	mTexture->Shutdown();
	mModel->Shutdown();

	delete mVS;
	delete mPS;
	delete mTexture;
	delete mModel;
}

void Game::Draw()
{
	mGraphics->InitDraw();

	mVS->BeginRender();
	mPS->BeginRender();

	MatrixBufferType matrixBuffer;
	D3DXMatrixTranspose(&matrixBuffer.world, &mGraphics->GetWorldMatrix());
	D3DXMatrixTranspose(&matrixBuffer.view, &mGraphics->GetViewMatrix());
	D3DXMatrixTranspose(&matrixBuffer.projection, &mGraphics->GetProjectionMatrix());

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
				outerColor = { 0, 0, 0, 1 };
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

		for (int i = 0; i < 4; ++i)
		{
			int x = pastPoints[i].x;
			int y = pastPoints[i].y;
			DrawBlock(x, y, { 1, 1, 0, 1, }, { 1, 0, 0, 1 });
		}
		for (int i = 0; i < 4; ++i)
		{
			DrawBlock(currentBodies[i]->x, currentBodies[i]->y, { 0.2f, 0.2f, 0.2f, 1 }, { 0, 0, 0, 1 });
		}
	}

	mPS->EndRender();
	mVS->EndRender();
	mGraphics->EndDraw();
}

void Game::DrawBlock(int x, int y, D3DXVECTOR4 outerColor, D3DXVECTOR4 innerColor)
{
	int leftMargin = 50;
	int bottomMargin = 50;

	const int width = 25;
	const int height = 25;
	const int numVertices = 6;
	const float edgeRatio = 0.1f;

	const D3DXVECTOR3 positions[numVertices] =
	{
		{ 0, 0, 0 },
		{ 0, 1, 0 },
		{ 1, 1, 0 },
		{ 1, 1, 0 },
		{ 1, 0, 0 },
		{ 0, 0, 0 }
	};
	const D3DXVECTOR2 texPositions[numVertices] =
	{
		{ 0, 0 },
		{ 0, 1 },
		{ 1, 0 },
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 }
	};

	D3DXVECTOR3 sqPosition[numVertices];
	memcpy_s(sqPosition, sizeof(sqPosition), positions, sizeof(positions));

	for (int i = 0; i < numVertices; ++i)
	{
		sqPosition[i][0] += x;
		sqPosition[i][1] += y;

		sqPosition[i][0] *= width;
		sqPosition[i][1] *= height;

		sqPosition[i][0] += leftMargin;
		sqPosition[i][1] += bottomMargin;
	}

	mModel->SetRGBA(outerColor);
	mModel->SetVertex(mGraphics->GetDevice(), numVertices, sqPosition);
	//mModel->SetVertex(mGraphics->GetDevice(), numVertices, sqPosition, texPositions);
	mModel->Render(mGraphics->GetDeviceContext());
	mModel->Shutdown();

	mGraphics->GetDeviceContext()->DrawIndexed(mModel->GetIndexCount(), 0, 0);

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
	}

	mModel->SetRGBA(innerColor);
	mModel->SetVertex(mGraphics->GetDevice(), numVertices, sqPosition);
	mModel->Render(mGraphics->GetDeviceContext());
	mModel->Shutdown();

	mGraphics->GetDeviceContext()->DrawIndexed(mModel->GetIndexCount(), 0, 0);
}