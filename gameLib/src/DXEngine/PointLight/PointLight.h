#pragma once
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/DXEngine/Shader/VertexShader/VertexShader.h"
#include "../../src/DXEngine/Shader/PixelShader/PixelShader.h"

//
////------------------------------------------------------------------
////!@class		PointLight
////!@brief	点光源
////------------------------------------------------------------------
//class PointLight
//{
//public:
//	//!@brief	コンストラクタ
//	PointLight();
//	//!@brief	デストラクタ
//	virtual ~PointLight();
//public:
//	//!@brief	更新
//	void	UpDate(Camera* camera);
//
//
//private:
//	struct ConstantBuffer
//	{
//		DirectX::XMFLOAT4X4	world;
//		DirectX::XMFLOAT4X4	view;
//		DirectX::XMFLOAT4X4	projection;
//		DirectX::XMFLOAT4	lightPos;
//		DirectX::XMFLOAT4	attenuation;
//	};
//private:
//	Math::Vector4	position;		//位置
//	Math::Vector4	attenuation;	//減衰量
//	Math::Vector4	color;			//色
//	ID3D11Buffer*	constantBuf;	//定数バッファ
//	ConstantBuffer	constant;
//	VertexShader*	vertexShader;
//	PixelShader*	pixelShader;
//};
//
