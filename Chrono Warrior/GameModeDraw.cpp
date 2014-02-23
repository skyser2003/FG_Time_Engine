#include "stdafx.h"
#include "GameMode.h"

#include "Canvas/DxCanvas.h"
#include "Graphics/graphicsclass.h"
#include "Shaders/VertexShader/VertexShader.h"
#include "Shaders/PixelShader/PixelShader.h"
#include "TextureManager/TextureManager.h"
#include "Texture/textureclass.h"

#include "WindowManager.h"
#include "Window.h"

#include "Map.h"
#include "Tile.h"
#include "FieldUnit.h"

namespace CW
{
	struct VertexType
	{
		D3DXVECTOR4 position;
		D3DXVECTOR4 color;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

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

		auto& tm = mCanvas->GetTextureManager();
		tm.SetDevice(mCanvas->GetDevice());

		mLemon = tm.CreateTexture("Data/lemon.jpg");
		mApple = tm.CreateTexture("Data/apple.jpg");
		mSoldier = tm.CreateTexture("Data/scv.jpg");
		mMage = tm.CreateTexture("Data/mage.jpg");
	}

	void GameMode::DrawTile(Tile* tile)
	{
		const int numVertices = 6;

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
		VertexType* vertices = new VertexType[numVertices];

		D3DXVECTOR4 sqPosition[numVertices];
		// Outer square
		memcpy_s(sqPosition, sizeof(sqPosition), positions, sizeof(positions));

		for (int i = 0; i < numVertices; ++i)
		{
			sqPosition[i][0] += tile->GetX();
			sqPosition[i][1] += tile->GetY();

			sqPosition[i][0] *= mTileWidth;
			sqPosition[i][1] *= mTileHeight;

			sqPosition[i][0] += mLeftMargin;
			sqPosition[i][1] += mBottomMargin;

			vertices[i].position = sqPosition[i];
			vertices[i].color = D3DXVECTOR4(1, 1, 1, 1);
			vertices[i].texture = texPositions[i];
			vertices[i].normal = D3DXVECTOR3(0, 0, 0);
		}

		info.noVertices = numVertices;
		info.buffer = vertices;
		info.bufferSize = sizeof(*vertices) * numVertices;

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
		VertexType* vertices = new VertexType[numVertices];

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

			vertices[i].position = sqPosition[i];
			vertices[i].color = D3DXVECTOR4(1, 1, 1, 1);
			vertices[i].texture = texPositions[i];
			vertices[i].normal = D3DXVECTOR3(0, 0, 0);
		}

		info.noVertices = numVertices;
		info.buffer = vertices;
		info.bufferSize = sizeof(*vertices) * numVertices;

		switch (unit->GetUnitType())
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

		if (unit == mSelectedUnit.get())
		{
			for (int i = 0; i < numVertices; ++i)
			{
				vertices[i].color = D3DXVECTOR4(1, 0, 1, 1);
			}
		}

		mCanvas->AddRenderInfo(info);
	}

	int GameMode::GetTileX(WORD screenX) const
	{
		return (screenX - mLeftMargin) / mTileWidth;
	}
	int GameMode::GetTileY(WORD screenY) const
	{
		return (screenY - mLeftMargin) / mTileHeight;
	}
	Position GameMode::GetTilePosition(WORD screenX, WORD screenY) const
	{
		return Position(GetTileX(screenX), GetTileY(screenY));
	}
}