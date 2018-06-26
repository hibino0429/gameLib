#pragma once

#include <string>
#include "../../src/Engine/DXEngine/DXEngine.h"
#include "../../src/Shader/VertexShader/VertexShader.h"
#include "../../src/Shader/PixelShader/PixelShader.h"
#include "../../src/Math/Math.h"

//----------------------------------------------------------------------------------------
//!@class		Sample
//!@brief	サンプルで扱うプログラムを作成するファイル
//----------------------------------------------------------------------------------------
class VertexPolygon
{
public:
	VertexPolygon();
	~VertexPolygon();

	void	UpDate();
	void	Render();


private:
	struct Vertex
	{
		float pos[3];
		float color[4];
	};

	ID3D11Buffer*	vertexBuffer;
	unsigned int stride;
	unsigned int offset;

	VertexShader vertexShader;
	PixelShader pixelShader;

	ID3D11Buffer*	indexBuffer;
};