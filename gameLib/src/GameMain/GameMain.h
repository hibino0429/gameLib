#pragma once
#include "../../src/VertexBuffer/VertexBuffer.h"
#include "../../src/Texture/Texture.h"
#include "../../src/Camera/Camera.h"
#include "../../src/Shader/VertexShader/VertexShader.h"
#include "../../src/Shader/PixelShader/PixelShader.h"
#include "../../src/Mesh/Mesh.h"

#include "../../src/Sample/Sample.h"


//--------------------------------------------------------------------------------------
//ゲームメイン
//--------------------------------------------------------------------------------------
class GameMain
{
public:
	GameMain();
	~GameMain();

	//更新処理
	void	UpDate();	
	//描画処理
	void	Render();

private:
	Camera*			camera;

private:
	Mesh*		mesh;
	Texture*	texture;

	Sample*		sample;
};