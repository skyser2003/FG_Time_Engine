#include "stdafx.h"
#include "GameMode.h"

#include "DxCanvas.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "WindowManager.h"
#include "Window.h"

#include "Map.h"
#include "Tile.h"
#include "FieldUnit.h"

namespace CW
{
	void GameMode::Draw(float dt)
	{
		mCanvas->BeginRender();

		mMap->ForeachTile([](Tile* tile)
		{

		});

		mCanvas->Render();
		mCanvas->EndRender();
	}

	void GameMode::InitializeGraphics()
	{
		std::string vsFileName = "C:/Projects/Shaders/vstexture.hlsl";
		std::string psTextureFileName = "C:/Projects/Shaders/pstexture.hlsl";
		std::string psColorFileName = "C:/Projects/Shaders/pscolor.hlsl";

		mCanvas = &GetWindow()->GetCanvas();

		mVS = mCanvas->CreateVertexShader();
		mVS->CompileShader(vsFileName.c_str(), "VertexTextureMain");
		mVS->SetupShaderBufferInputType("POSITION");
		mVS->SetupShaderBufferInputType("TEXCOORD");
		mVS->SetupShaderBufferInputType("COLOR");
		mVS->CreateShaderBufferDesc();
		mVS->CreateCBufferDesc("matrix", sizeof(MatrixBufferType));

		mPS = mCanvas->CreatePixelShader();
		mPS->CompileShader(psTextureFileName.c_str(), "PixelTextureMain");
		mPS->CreateSamplerState();
	}
}