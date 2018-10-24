#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/CollisionData/CollisionData.h"
#include "../../src/Component/Collision/CapsuleCollider/CapsuleCollider.h"



//----------------------------------------------------------------------------
//!@class		AABB
//!@brief	ワールド空間のXYZ軸に対して確変が平行な直方体の定義
//!@brief	[中心点]と[各軸の辺の長さの半分]で表す
//----------------------------------------------------------------------------
class AABB
{
public:
	//!@brief	コンストラクタ
	AABB();
	//!@brief	コンストラクタ
	//!@param[in]	centerPos	中心点
	//!@param[in]	sideHalfLength	各軸の辺の半分の長さ
	AABB(const Math::Vector3& centerPos, const Math::Vector3& sideHalfLength);
public:
	//!@brief	X軸の辺の長さの取得
	//!@return	x軸の長さ
	const float&	GetLengthX() const;
	//!@brief	Y軸の辺の長さの取得
	//!@return	y軸の長さ
	const float&	GetLengthY() const;
	//!@brief	Z軸の辺の長さの取得
	//!@return	z軸の長さ
	const float&	GetLengthZ() const;
	//!@brief	中心座標の取得
	//!@return	中心座標(x,y,z)
	const Math::Vector3&	GetCenterPos() const;
public:
	//!@brief	左上奥の座標の取得
	const Math::Vector3&	GetLeftUpBackPos() const;
	//!@brief	左上手前の座標の取得
	const Math::Vector3&	GetLeftUpFrontPos() const;
	//!@brief	左下奥の座標の取得
	const Math::Vector3&	GetLeftDownBackPos() const;
	//!@brief	左下手前の座標の取得
	const Math::Vector3&	GetLeftDownFrontPos() const;
	//!@brief	右上奥の座標の取得
	const Math::Vector3&	GetRightUpBackPos() const;
	//!@brief	右上手前の座標の取得
	const Math::Vector3&	GetRightUpFrontPos() const;
	//!@brief	右下奥の座標の取得
	const Math::Vector3&	GetRightDownBackPos() const;
	//!@brief	右下手前の座標の取得
	const Math::Vector3&	GetRightDownFrontPos() const;
public:
	//!@brief	線分との当たり判定
	//!@param[in]	segment	線分
	bool	HitSegment(Segment& segment);
private:
	AABBData		data;
};

