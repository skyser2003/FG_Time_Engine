#include "stdafx.h"
#include "GameMode.h"

#include "DxCanvas.h"
#include "graphicsclass.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "textureclass.h"

#include "WindowManager.h"
#include "Window.h"

#include "Map.h"
#include "Tile.h"
#include "FieldUnit.h"

namespace CW
{
	void GameMode::Draw(std::chrono::system_clock::duration dt)
	{
		mCanvas->BeginRender();
		mCanvas->EquipPixelShader(mPS);
		mCanvas->EquipVertexShader(mVS);
		mPS->SetTexture(mLemon->GetTexture());

		FG::MatrixBufferType matrixBuffer;
		D3DXMatrixTranspose(&matrixBuffer.world, &mCanvas->GetGraphics()->GetWorldMatrix());
		D3DXMatrixTranspose(&matrixBuffer.view, &mCanvas->GetGraphics()->GetViewMatrix());
		D3DXMatrixTranspose(&matrixBuffer.projection, &mCanvas->GetGraphics()->GetProjectionMatrix());
		mVS->SetCBufferDesc("matrix", &matrixBuffer, sizeof(matrixBuffer));

		// Draw tile
		mMap->ForeachTile([&, this](Tile* tile)
		{
			this->DrawTile(tile);
		});
		// Draw unit
		mMap->ForeachUnit([&, this](FieldUnit* unit)
		{
			this->DrawUnit(unit);
		});

		mCanvas->Render();
		mCanvas->EndRender();
	}

	void GameMode::InitializeGraphics()
	{
		HRESULT result;
		std::string vsFileName = "C:/Projects/Shaders/vstexture.hlsl";
		std::string psTextureFileName = "C:/Projects/Shaders/pstexture.hlsl";
		std::string psColorFileName = "C:/Projects/Shaders/pscolor.hlsl";

		mCanvas = &GetWindow()->GetCanvas();

		mVS = mCanvas->CreateVertexShader();
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

		mPS = mCanvas->CreatePixelShader();
		//result = mPS->CompileShader(psColorFileName.c_str(), "PixelColorMain");
		result = mPS->CompileShader(psTextureFileName.c_str(), "PixelTextureMain");
		if (FAILED(result))
		{
			MessageBox(mCanvas->GetHwnd(), "Error compiling shader.  Check shader-error.txt for message.", psTextureFileName.c_str(), MB_OK);
			return;
		}
		mPS->CreateSamplerState();

		mLemon.reset(new FG::TextureClass);
		mApple.reset(new FG::TextureClass);
		mSoldier.reset(new FG::TextureClass);
		mMage.reset(new FG::TextureClass);

		mLemon->Initialize(mCanvas->GetDevice(), "C:/Projects/FGEngine/FG_Time_Engine/Chrono Warrior/Data/lemon.jpg");
		mApple->Initialize(mCanvas->GetDevice(), "C:/Projects/FGEngine/FG_Time_Engine/Chrono Warrior/Data/apple.jpg");
		mSoldier->Initialize(mCanvas->GetDevice(), "C:/Projects/FGEngine/FG_Time_Engine/Chrono Warrior/Data/scv.jpg");
		mMage->Initialize(mCanvas->GetDevice(), "C:/Projects/FGEngine/FG_Time_Engine/Chrono Warrior/Data/mage.jpg");
	}

	void GameMode::DrawTile(Tile* tile)
	{
		const int numVertices = 6;
		const int width = 50;
		const int height = 50;
		int leftMargin = 50;
		int bottomMargin = 50;

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

		FG::RenderInfo info;
		info.noVertices = numVertices;
		info.position.resize(numVertices);
		info.texPosition.resize(numVertices);

		D3DXVECTOR4 sqPosition[numVertices];
		// Outer square
		memcpy_s(sqPosition, sizeof(sqPosition), positions, sizeof(positions));

		for (int i = 0; i < numVertices; ++i)
		{
			sqPosition[i][0] += tile->GetX();
			sqPosition[i][1] += tile->GetY();

			sqPosition[i][0] *= width;
			sqPosition[i][1] *= height;

			sqPosition[i][0] += leftMargin;
			sqPosition[i][1] += bottomMargin;

			info.position[i] = sqPosition[i];
			info.texPosition[i] = texPositions[i];
		}

		info.color = D3DXVECTOR4(1, 1, 1, 1);

		switch (tile->GetType())
		{
		case Tile::TILE_SPACE:
			info.texture = mApple.get();
			break;
		case Tile::TILE_ROAD:
			info.texture = mLemon.get();
			break;
		}

		mCanvas->AddRenderInfo(info);
	}
	void GameMode::DrawUnit(FieldUnit* unit)
	{
		const int numVertices = 6;
		const int width = 50;
		const int height = 50;
		int leftMargin = 50;
		int bottomMargin = 50;

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

		FG::RenderInfo info;
		info.noVertices = numVertices;
		info.position.resize(numVertices);
		info.texPosition.resize(numVertices);

		D3DXVECTOR4 sqPosition[numVertices];
		// Outer square
		memcpy_s(sqPosition, sizeof(sqPosition), positions, sizeof(positions));

		for (int i = 0; i < numVertices; ++i)
		{
			sqPosition[i][0] += unit->GetX();
			sqPosition[i][1] += unit->GetY();

			sqPosition[i][0] *= width;
			sqPosition[i][1] *= height;

			sqPosition[i][0] += leftMargin;
			sqPosition[i][1] += bottomMargin;

			info.position[i] = sqPosition[i];
			info.texPosition[i] = texPositions[i];
		}

		info.color = D3DXVECTOR4(1, 1, 1, 1);

		switch (unit->GetUnitTYpe())
		{
		case FieldUnit::FU_CHRONO_SOLDIER:
			info.texture = mSoldier.get();
			break;
		case FieldUnit::FU_CHRONO_MAGE:
			info.texture = mMage.get();
			break;
		case FieldUnit::FU_DEFAULT:
			info.texture = mApple.get();
			break;
		}

		mCanvas->AddRenderInfo(info);
	}
}