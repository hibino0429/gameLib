#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Triangle2D
//!@brief	三角形(2D)を定義
//!@brief	[点]を3つ用意して表す
//----------------------------------------------------------------------------
class Triangle2D
{
public:
	//!@brief	コンストラクタ
	Triangle2D();
	//!@brief	コンストラクタ
	//!@param[in]	point1	点1
	//!@param[in]	point2	点2
	//!@param[in]	point3	点3
	Triangle2D(const Math::Vector2& point1, const Math::Vector2& point2, const Math::Vector2& point3);
public:
	//!@brief	辺の長さを取得
	//!@param[in]	vectorNo	ベクトルNo
	//!@return	辺の長さ
	const float	GetLength(int vectorNo) const;
	//!@brief	辺ベクトル(非正規化)を取得
	//!@param[in]	vectorNo	ベクトルNo
	//!@return	辺ベクトル
	const Math::Vector2&	GetVector(int vectorNo) const;
	//!@brief	頂点の取得
	//!@param[in]	pointNo	頂点番号
	const Math::Vector2&	GetPoint(int pointNo) const;
private:
	Math::Vector2	point[3];
};