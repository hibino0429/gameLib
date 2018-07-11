#include "Material.h"

#include <fstream>
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"


//-----------------------------------------------------------------------------
//!@brief	コンストラクタ
//-----------------------------------------------------------------------------
Material::Material()
	: vertexShader(new VertexShader())
	, pixelShader(new PixelShader())
{

}

//-----------------------------------------------------------------------------
//!@brief	デストラクタ
//-----------------------------------------------------------------------------
Material::~Material()
{
	Utility::SafeDelete(vertexShader);
	Utility::SafeDelete(pixelShader);
}

//-----------------------------------------------------------------------------
//!@brief	シェーダーファイルを読み込む
//!@param[in]	filePath	ファイルパス
//-----------------------------------------------------------------------------
void	Material::Load(const std::string& filePath)
{
	//ファイル読み込み
	std::ifstream sourceFile(filePath.c_str());
	std::istreambuf_iterator<char> iterator(sourceFile);
	std::istreambuf_iterator<char> last;
	std::string source(iterator, last);
	sourceFile.close();
	//マテリアル(シェーダ)の作成
	Create(source);
}

//-----------------------------------------------------------------------------
//!@brief	マテリアルの生成
//!@param[in]	shaderSource	シェーダーのソース
//-----------------------------------------------------------------------------
void	Material::Create(const std::string& shaderSource)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC>	inputElementDesc;

	inputElementDesc.push_back({
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		0,
		0,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	inputElementDesc.push_back({
		"NORMAL",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		12,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	inputElementDesc.push_back({
		"TEXCOORD",
		0,
		DXGI_FORMAT_R32G32_FLOAT,
		0,
		24,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	inputElementDesc.push_back({
		"BLENDINDICES",
		0,
		DXGI_FORMAT_R32G32B32A32_UINT,
		0,
		32,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	inputElementDesc.push_back({
		"BLENDINDICES",
		1,
		DXGI_FORMAT_R32G32B32A32_UINT,
		0,
		48,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	inputElementDesc.push_back({
		"BLENDWEIGHT",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		0,
		64,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	inputElementDesc.push_back({
		"BLENDWEIGHT",
		1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		0,
		80,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });

	if (!vertexShader->Create("./data/shaderData/testShader", inputElementDesc.data(), inputElementDesc.size()))
	{
		MessageBoxA(nullptr, "失敗", "頂点シェーダ", MB_OK);
	}
	if (!pixelShader->Create("./data/shaderData/testShader"))
	{
		MessageBoxA(nullptr, "失敗", "ピクセルシェーダ", MB_OK);
	}

}

//-----------------------------------------------------------------------------
//!@brief	シェーダーで使用するコンスタントバッファの設定
//!@param[in]	slot	設定する番号
//!@param[in]	constantBuf	コンスタントバッファ
//!@param[in]	size	バッファの大きさ
//-----------------------------------------------------------------------------
void	Material::SetConstantBuffer(const int slot, void* constantBuf, size_t size)
{
	constantBuffer[slot].ptr = constantBuf;
	if (constantBuffer[slot].buffer != nullptr)
	{
		constantBuffer[slot].buffer->Release();
	}
	D3D11_BUFFER_DESC	constantDesc;
	SecureZeroMemory(&constantDesc, sizeof(constantDesc));
	constantDesc.ByteWidth = size;
	constantDesc.Usage = D3D11_USAGE_DEFAULT;
	constantDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	auto result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(
		&constantDesc,
		nullptr,
		&constantBuffer[slot].buffer
	);
	if (FAILED(result))
	{
		//エラー
	}
}

//-----------------------------------------------------------------------------
//!@brief	シェーダーで使用するテクスチャの設定
//!@param[in]	slot	設定する番号
//!@param[in]	texture	テクスチャ
//-----------------------------------------------------------------------------
void	Material::SetTexture(const int slot, Texture* texture)
{
	textures[slot] = texture;
}

//-----------------------------------------------------------------------------
//!@brief	シェーダーをグラフィックスにアタッチ
//-----------------------------------------------------------------------------
void	Material::Attach()
{
	vertexShader->Set();
	pixelShader->Set();
	
	for (int i = 0; i < 10; ++i)
	{
		if (constantBuffer[i].ptr != nullptr)
		{
			Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuffer[i].buffer, 0, nullptr, constantBuffer[i].ptr, 0,0);
			Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetConstantBuffers(i, 1, &constantBuffer[i].buffer);
			Engine<DXDevice>::GetDevice().GetDeviceContext3D().HSSetConstantBuffers(i, 1, &constantBuffer[i].buffer);
			Engine<DXDevice>::GetDevice().GetDeviceContext3D().DSSetConstantBuffers(i, 1, &constantBuffer[i].buffer);
			Engine<DXDevice>::GetDevice().GetDeviceContext3D().GSSetConstantBuffers(i, 1, &constantBuffer[i].buffer);
			Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetConstantBuffers(i, 1, &constantBuffer[i].buffer);
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		if (textures[i] != nullptr)
		{
			textures[i]->Attach(i);
		}
	}
}