#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/Segment3D/Segment3D.h"

//----------------------------------------------------------------------------
//!@class		Capsule3D
//!@brief	3D空間でカプセルを定義する
//!@brief	[線分]に[半径]が追加されて表す
//----------------------------------------------------------------------------
class Capsule3D
{
public:
	//!@brief	コンストラクタ
	Capsule3D();
	//!@brief	コンストラクタ
	//!@param[in]	segment	線分
	//!@param[in]	radius	半径
	Capsule3D(const Segment3D& segment, const float radius);
	//!@brief	コンストラクタ
	//!@param[in]	point1	点1
	//!@param[in]	point2	点2
	//!@param[in]	radius	半径
	Capsule3D(const Point3D& point1, const Point3D& point2, const float radius);
public:
	//!@brief	線分の取得
	//!@return	線分
	const Segment3D&	GetSegment() const;
	//!@brief	半径の取得
	//!@return	半径
	const float&	GetRadius() const;
private:
	Segment3D	segment;
	float		radius;
};