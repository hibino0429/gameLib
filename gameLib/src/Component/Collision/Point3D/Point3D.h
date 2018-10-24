#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Point3D
//!@brief	3D空間に点を定義する
//!@brief	[x,y,z]の座標で点を表す
//----------------------------------------------------------------------------
class Point3D : public Math::Vector3
{
public:
	//!@brief	コンストラクタ
	Point3D();
	//!@brief	コンストラクタ
	//!@param[in]	point	点
	Point3D(const Math::Vector3& point);
	//!@brief	コンストラクタ
	//!@param[in]	x	座標x
	//!@param[in]	y	座標y
	//!@param[in]	z	座標z
	Point3D(const float x, const float y, const float z);
public:
	//!@brief	点座標の取得
	//!@return	点の座標
	const Math::Vector3&	GetPointPos() const;
};