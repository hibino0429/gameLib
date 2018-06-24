#pragma once

#include <string>
#include "../../src/Engine/DXEngine/DXEngine.h"
#include "../../src/Shader/VertexShader/VertexShader.h"
#include "../../src/Shader/PixelShader/PixelShader.h"


//----------------------------------------------------------------------------------------
//!@class		Sample
//!@brief	�T���v���ň����v���O�������쐬����t�@�C��
//----------------------------------------------------------------------------------------
class Sample
{
public:
	Sample();
	~Sample();

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
};