#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/Point3D/Point3D.h"

//----------------------------------------------------------------------------
//!@class		Sphere
//!@brief	3D空間で球体を定義する
//!@brief	[中心点]と[半径]で表す
//----------------------------------------------------------------------------
class Sphere
{
public:
	//!@brief	コンストラクタ
	Sphere();
	//!@brief	コンストラクタ
	//!@param[in]	centerPos	中心点
	//!@param[in]	radius	半径
	Sphere(const Point3D& centerPoint, const float radius);
public:
	//!@brief	中心点の取得
	//!@return	半径(Point3D)
	const Point3D&	GetCenterPoint() const;
	//!@brief	半径の取得
	//!@return	半径(float)
	const float		GetRadius() const;
private:
	Point3D		point;
	float		radius;
};