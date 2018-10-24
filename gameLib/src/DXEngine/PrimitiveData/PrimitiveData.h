#pragma once
#include <vector>
#include <atlbase.h>
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/DXEngine/Shader/VertexShader/VertexShader.h"
#include "../../src/DXEngine/Shader/PixelShader/PixelShader.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/DXEngine/Vertex/Vertex.h"


//-------------------------------------------------------------------------
//!@class		PrimitiveData
//!@brief	頂点バッファやインデックスバッファを扱う
//!@brief	頂点のデータやインデックスのデータを保持する
//-------------------------------------------------------------------------
class Primitive
{
public:
	Primitive();
	~Primitive();
public:
	//!@適用させる
	void	Attach();
	//!@brief	頂点データを追加する
	void	AddVertexData(const Vertex& vertexData);
	//!@brief	インデックスデータを追加する
	void	AddIndexData(const int& indexData);

	//!@brief	頂点データを追加する
	void	AddVertexDatas(const std::vector<Vertex>&	vertexData);
	//!@brief	インデックスデータを追加
	void	AddIndexDatas(const std::vector<int>& indexData);
	//!@brief	頂点バッファの作成
	void	CreateVertexBuffer();
	//!@brief	インデックスバッファの作成
	void	CreateIndexBuffer();
	//!@brief	頂点データを更新する
	//!@param[in]	頂点データ	vertexData
	void	UpDateVertexDatas(const std::vector<Vertex>& vertexData);
	//!@brief	ラスタライザの設定
	//!@param[in]	fillMode	色を塗るか、ワイヤーフレームのモード
	//!@param[in]	cullMode	両面描画、表面、裏面のモード
	void	SetDrawMode(const D3D11_FILL_MODE& fillMode, const D3D11_CULL_MODE& cullMode);
private:
	ATL::CComPtr<ID3D11Buffer>	vertexBuffer;
	ATL::CComPtr<ID3D11Buffer>	indexBuffer;
	ATL::CComPtr<ID3D11RasterizerState>	rasterizerState;
	std::vector<Vertex>	vertices;	//頂点データ
	std::vector<int>	indices;	//インデックスデータ
};