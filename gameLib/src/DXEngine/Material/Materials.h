#pragma once
#include <vector>
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/DXEngine/Texture/Texture.h"
#include "../../src/DXEngine/Shader/VertexShader/VertexShader.h"
#include "../../src/DXEngine/Shader/PixelShader/PixelShader.h"

//-------------------------------------------------------------------
//!@class		Materials
//!@brief	マテリアル情報を扱う
//!@brief	シェーダを使用して色情報を扱います
//-------------------------------------------------------------------
class Materials
{
public:
	//!@brife	定数バッファの定義
	struct ConstantBuffer
	{
		ConstantBuffer() : ptr(nullptr), buffer(nullptr) {};
		void*			ptr;
		ID3D11Buffer*	buffer;
	};

public:
	//!@brief	コンストラクタ
	Materials();
	//!@brief	デストラクタ
	~Materials();

	//!@brief	シェーダーファイルを読み込む
	//!@param[in]	filePath	ファイルパス
	void	Load(const std::string& filePath);
	
	//!@brief	マテリアルの生成
	//!@param[in]	shaderSource	シェーダーのソース
	void	Create(const std::string& shaderSource);

	//!@brief	シェーダーで使用するコンスタントバッファの設定
	//!@param[in]	slot	設定する番号
	//!@param[in]	constantBuf	コンスタントバッファ
	//!@param[in]	size	バッファの大きさ
	void	SetConstantBuffer(const int slot, void* constantBuf, size_t size);

	//!@brief	シェーダーで使用するテクスチャの設定
	//!@param[in]	slot	設定する番号
	//!@param[in]	texture	テクスチャ
	void	SetTexture(const int slot, Texture* texture);

	//!@brief	シェーダーをグラフィックスにアタッチ
	void	Attach();
private:
	Texture*		textures[10];
	ConstantBuffer	constantBuffer[10];
	VertexShader*	vertexShader;
	PixelShader*	pixelShader;
};