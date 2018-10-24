#pragma once
#include "../../src/DXEngine/Math/Math.h"


//ライトの種類
enum LightType
{
	Point = 1,
	Spot = 2,
	Directional = 3,
};

//ライトの構造体
struct LightData
{
	LightType		type;			//ライトの種類
	Math::Vector3	color;			//ライトの色
};




//平行光源の定数バッファ
struct DirLightCBuffer
{
	DirectX::XMFLOAT4X4	world;
	DirectX::XMFLOAT4X4	view;
	DirectX::XMFLOAT4X4	projection;
	DirectX::XMFLOAT4	lightDirection;
	DirectX::XMFLOAT4	lightColor;
};

//-------------------------------------------
//!@class		平行光源データ
//-------------------------------------------
struct DirectinalLightData
{
	Math::Vector3	lightDir;		//光の向き
};


//ポイントライトの定数バッファ
struct PointLightCBuffer
{
	DirectX::XMFLOAT4X4	world;
	DirectX::XMFLOAT4X4	view;
	DirectX::XMFLOAT4X4	projection;
	DirectX::XMFLOAT4	lightPos;
	DirectX::XMFLOAT4	attenuation;
	DirectX::XMFLOAT4	lightColor;
};

//-------------------------------------------
//!@class		点光源データ
//-------------------------------------------
struct PointLightData
{
	Math::Vector3	pos;			//光源位置
	Math::Vector3	attenuation;	//減衰パラメータ
};
