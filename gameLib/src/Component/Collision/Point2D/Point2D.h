#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Point2D
//!@brief	点を定義
//!@brief	[点]を持つ
//----------------------------------------------------------------------------
class Point2D
{
public:
	//!@brief	コンストラクタ
	Point2D();
	//!@brief	コンストラクタ
	//!@param[in]	point	点
	Point2D(const Math::Vector2& point);
public:
	//!@brief	点の取得
	//!@return	点
	const Math::Vector2&	GetPoint() const;
	//!@brief	点と点の当たり判定
	//!@param[in]	targetPoint	相手側の点
	//!@return	true: 衝突 false: 衝突していない
	bool	Hit(const Point2D& targetPoint);
private:
	Math::Vector2	point;
	float			permissible;	//許容範囲
};
