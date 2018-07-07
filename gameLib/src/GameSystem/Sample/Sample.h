#pragma once

#include <string>
#include "../../src/DXEngine/Shader/VertexShader/VertexShader.h"
#include "../../src/DXEngine/Shader/PixelShader/PixelShader.h"
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"

//----------------------------------------------------------------------------------------
//!@class		Sample
//!@brief	サンプルで扱うプログラムを作成するファイル
//----------------------------------------------------------------------------------------
class Sample
{
public:
	Sample();
	~Sample();

	void	UpDate();
	void	Render();

	void	SetViewMat(const DirectX::XMFLOAT4X4& viewMat);
	void	SetProjMat(const DirectX::XMFLOAT4X4& projMat);

private:
	struct Vertex
	{
		float pos[3];
		float color[4];
		float uv[2];
	};
	
	struct Vex
	{
		float pos[3];
		float uv[2];
	};
	struct ConstantBuf
	{
		DirectX::XMFLOAT4X4	world;
		DirectX::XMFLOAT4X4	view;
		DirectX::XMFLOAT4X4	projection;
	};

	ID3D11Buffer*	constantBuffer;
	ID3D11Buffer*	vertexBuffer;
	ID3D11Buffer*	indexBuffer;
	unsigned int stride;
	unsigned int offset;

	VertexShader	vertexShader;
	PixelShader		pixelShader;

	Math::Vector3		pos;
	Math::Vector3		angle;
	Math::Vector3		scale;

	D3D11_INPUT_ELEMENT_DESC* inputLayout;
};