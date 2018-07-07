#pragma once

#include "../../src/DXEngine/VertexBuffer/VertexBuffer.h"
#include "../../src/DXEngine/Texture/Texture.h"
#include "../../src/DXEngine/Camera/Camera.h"
#include "../../src/DXEngine/Shader/VertexShader/VertexShader.h"
#include "../../src/DXEngine/Shader/PixelShader/PixelShader.h"
#include "../../src/DXEngine/Mesh/Mesh.h"
#include "../../src/GameSystem/Sample/Sample.h"
#include "../../src/DXEngine/Model/Model.h"
#include "../../src/GameSystem/Particle/Particle.h"

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
	Mesh*			mesh;
	Texture*		texture;
	
	Sample*			sample;
	Model*			model;
	Particle*		particle;
	int				timeCnt;
	int				cnt;
};