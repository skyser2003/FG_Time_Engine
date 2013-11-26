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
	const int width = 50;
	const int height = 50;
	const int numVertices = 6;
	const D3DXVECTOR3 positions[numVertices] =
	{
		{ -1, 1, 0 },
		{ -1, -1, 0 },
		{ 1, 1, 0 },
		{ 1, 1, 0 },
		{ 1, -1, 0 },
		{ -1, -1, 0 }
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

	mGraphics->InitDraw();

	mVS->BeginRender();
	mPS->BeginRender();

	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 10; ++i)
		{
			D3DXVECTOR3 sqPosition[numVertices];
			memcpy_s(sqPosition, sizeof(sqPosition), positions, sizeof(positions));

			for (int i = 0; i < numVertices; ++i)
			{
				sqPosition[i][0] += i;
				sqPosition[i][1] = j;

				sqPosition[i][0] *= width;
				sqPosition[i][1] *= height;
			}

			mModel->SetRGBA(0, 1, 1, 1);
			mModel->SetVertex(mGraphics->GetDevice(), numVertices, sqPosition, texPositions);
			mModel->Render(mGraphics->GetDeviceContext());
			mModel->Shutdown();

			mGraphics->GetDeviceContext()->DrawIndexed(mModel->GetIndexCount(), 0, 0);
		}
	}


	mPS->EndRender();
	mVS->EndRender();
	mGraphics->EndDraw();

	/*system("cls");

	auto field = map->GetField();

	std::array<Point, 4> pastPoints;

	if (currentBlock)
	{
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
	}

	for (int j = 19; j >= 0; --j)
	{
		printf("бс");

		for (int i = 0; i < 10; ++i)
		{
			bool pastDrawn = false;

			for (Point past : pastPoints)
			{
				if (past.x == i && past.y == j && field[i][j] != 1)
				{
					color_printf(FOREGROUND_RED | FOREGROUND_INTENSITY, "бс");
					pastDrawn = true;
					break;
				}
			}

			if (pastDrawn)
			{
				continue;
			}

			switch (field[i][j])
			{
			case 0: // empty
			{
						printf_s("бр");
			}
				break;
			case 1: // block
			{
						color_printf(FOREGROUND_BLUE | FOREGROUND_INTENSITY, "бс");
			}
				break;
			default:
			{
					   // error!
			}
				break;
			}
		}

		printf("бс");
		printf("\n");
	}

	for (int i = 0; i < 10 + 2; ++i)
	{
		printf("бс");
	}
	*/
}