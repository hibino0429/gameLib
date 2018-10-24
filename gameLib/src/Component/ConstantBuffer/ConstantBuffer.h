#pragma once
#include <d3d11.h>
#include <atlbase.h>
#include "../../src/DXEngine/Math/Math.h"



//!@brief	定数バッファ構造体
struct CBuffer 
{
	DirectX::XMFLOAT4X4	world;
	DirectX::XMFLOAT4X4	view;
	DirectX::XMFLOAT4X4	projection;
	DirectX::XMFLOAT4	lightDirection;
	DirectX::XMFLOAT4	lightColor;
};


//座標系変換行列データ
struct TransMatrix
{
	DirectX::XMMATRIX	worldMat;
	DirectX::XMMATRIX	viewMat;
	DirectX::XMMATRIX	projMat;

	//ヒープで割り当てられたオブジェクトが16にアライメントされていない
	//XMMATRIXを保持していると、このようなWarningが出る
	//保持するときは、XMFLOAT4X4を使用する
	/*DirectX::XMFLOAT4X4	worldMat;
	DirectX::XMFLOAT4X4	viewMat;
	DirectX::XMFLOAT4X4	projMat;*/
};

//-------------------------------------------------------
//!@class		ConstantBuffer
//!@brief	共通の定数バッファを保持する
//-------------------------------------------------------
class ConstantBuffer
{
public:
	//!@brief	コンストラクタ
	//!@brief	共通の定数バッファの場合
	ConstantBuffer();
	//!@brief	コンストラクタ
	//!@brief	定数バッファのサイズだけ渡す
	ConstantBuffer(const size_t& bufferSize);
	//!@brief	コンストラクタ
	//!@brief	独自の定数バッファの場合
	ConstantBuffer(const D3D11_BUFFER_DESC& cBufferDesc);
	//!@brief	デストラクタ
	~ConstantBuffer();
public:
	//!@brief	更新
	//!@param[in]	constantBuffer	定義した定数バッファ
	void	UpDate(void* constantBuffer);
	//!@brief	描画
	void	Render();
	//!@brief	定数バッファの設定
	//!@param[in]	cBuffer	定数バッファ
	//void	SetConstantBuffer(const CBuffer& cBuffer);
private:
	ATL::CComPtr<ID3D11Buffer>	constantBuf;
};
