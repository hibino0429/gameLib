#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/Segment2D/Segment2D.h"

//----------------------------------------------------------------------------
//!@class		Capsule2D
//!@brief	カブセル(2D)を定義
//!@brief	線分上を半径の球がスウィープした図形
//!@brief	[線分]と[半径]を持つ
//----------------------------------------------------------------------------
class Capsule2D
{
public:
	//!@brief	コンストラクタ
	Capsule2D();
	//!@brief	コンストラクタ
	//!@param[in]	segment	線分
	//!@param[in]	radius	半径
	Capsule2D(const Segment2D& segment, const float radius);
	//!@brief	コンストラクタ
	//!@param[in]	beginPoint	始点
	//!@param[in]	endPoint	終点
	//!@param[in]	radius	半径
	Capsule2D(const Math::Vector2& beginPoint, const Math::Vector2& endPoint, const float radius);
private:
	Segment2D	segment;
	float		radius;
};