#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Circle2D
//!@brief	円(2D)を定義
//!@brief	[中心点]と[半径]のみを持つ
//----------------------------------------------------------------------------
class Circle2D
{
public:
	//!@brief	コンストラクタ
	Circle2D();
	//!@brief	コンストラクタ
	//!@param[in]	centerPos	中心点
	//!@param[in]	radius	半径
	Circle2D(const Math::Vector2& centerPos, const float radius);
public:
	//!@brief	中心点の取得
	//!@return	中心点
	const Math::Vector2&	GetCenterPos() const;
	//!@brief	半径の取得
	//!@return	半径
	const float		GetRadius() const;
	//!@brief	中心点のオフセット
	//!@param[in]	offsetVolume	オフセット量
	void	OffsetCenterPos(const Math::Vector2& offsetVolume);
private:
	Math::Vector2	centerPos;
	float			radius;
};