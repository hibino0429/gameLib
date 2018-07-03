#pragma once
#include <vector>
#include "../../src/Device/DXDevice/DXDevice.h"
#include "../../src/Shader/VertexShader/VertexShader.h"
#include "../../src/Shader/PixelShader/PixelShader.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Vertex/Vertex.h"


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
	void	AddIndexData(const WORD& indexData);

	//!@brief	頂点データを追加する
	void	AddVertexDatas(const std::vector<Vertex>&	vertexData);
	//!@brief	インデックスデータを追加
	void	AddIndexDatas(const std::vector<int>& indexData);
	//!@brief	頂点バッファの作成
	void	CreateVertexBuffer();
	//!@brief	インデックスバッファの作成
	void	CreateIndexBuffer();
private:
	ID3D11Buffer*	vertexBuffer;
	ID3D11Buffer*	indexBuffer;

	std::vector<Vertex>	vertices;	//頂点データ
	std::vector<int>	indices;	//インデックスデータ
};