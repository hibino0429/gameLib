#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Line2D
//!@brief	直線(無限に伸びた線)を定義
//!@brief	[1つの点]と[方向ベクトル]を持つ
//----------------------------------------------------------------------------
class Line2D
{
public:
	//!@brief	コンストラクタ
	Line2D();
	//!@brief	コンストラクタ
	//!@param[in]	point		点
	//!@param[in]	dirVector	方向ベクトル
	Line2D(const Math::Vector2& point, const Math::Vector2& dirVector);
public:
	//!@brief	点上の座標を取得
	//!@param[in]	t	ベクトルにかける係数
	//!@return	点の座標
	const Math::Vector2&	GetPoint(const float t) const;
private:
	Math::Vector2	point;		//点
	Math::Vector2	dirVector;	//方向ベクトル
};

