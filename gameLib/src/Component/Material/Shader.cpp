#include "Shader.h"
#include "../../src/Utility/Utility.hpp"



Shader::Shader(const std::string& filePath)
	: filePath(filePath)
{
	vertexShader = new VertexShader();
	pixelShader = new PixelShader();

	vertexShader->SetEntryPointName("VS_main");
	pixelShader->SetEntryPointName("PS_main");
}

Shader::~Shader()
{
	Utility::SafeDelete(vertexShader);
	Utility::SafeDelete(pixelShader);
}



bool	Shader::CreateShaderParam(D3D11_INPUT_ELEMENT_DESC* inputDesc,const UINT elemNum)
{
	if (!vertexShader->Create(filePath, inputDesc, elemNum)) { return false; }
	if (!pixelShader->Create(filePath)) { return false; }
	return true;
}

bool	Shader::CreateTextureShaderParam()
{
	D3D11_INPUT_ELEMENT_DESC	inputDesc[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	if (!CreateShaderParam(inputDesc, ARRAYSIZE(inputDesc))) { return false; }
	return true;
}

bool	Shader::CreateColorShaderParam()
{
	D3D11_INPUT_ELEMENT_DESC	inputDesc[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	if (!CreateShaderParam(inputDesc, ARRAYSIZE(inputDesc))) { return false; }
	return true;
}

void	Shader::UpDate()
{
	vertexShader->Set();
	pixelShader->Set();
}