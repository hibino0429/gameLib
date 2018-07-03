#pragma once
#include "../../src/VertexBuffer/VertexBuffer.h"
#include "../../src/Texture/Texture.h"
#include "../../src/Camera/Camera.h"
#include "../../src/Shader/VertexShader/VertexShader.h"
#include "../../src/Shader/PixelShader/PixelShader.h"
#include "../../src/Mesh/Mesh.h"

#include "../../src/Sample/Sample.h"
#include "../../src/polygon/polygon.h"
#include "../../src/Particle/Particle.h"

//--------------------------------------------------------------------------------------
//�Q�[�����C��
//--------------------------------------------------------------------------------------
class GameMain
{
public:
	GameMain();
	~GameMain();

	//�X�V����
	void	UpDate();	
	//�`�揈��
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
};