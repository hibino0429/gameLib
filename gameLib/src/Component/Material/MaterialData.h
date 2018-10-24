#pragma once
#include "../../src/DXEngine/Texture/Texture.h"
#include "../../src/DXEngine/Shader/VertexShader/VertexShader.h"
#include "../../src/DXEngine/Shader/PixelShader/PixelShader.h"
#include "../../src/DXEngine/Math/Math.h"




//!@class	マテリアルのデータ
struct MaterialData
{
	Texture*		texture;
	VertexShader*	vertexShader;
	PixelShader*	pixelShader;
	Math::Vector4	diffuseColor;
};

