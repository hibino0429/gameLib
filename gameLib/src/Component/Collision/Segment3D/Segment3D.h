#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/Line3D/Line3D.h"


//----------------------------------------------------------------------------
//!@class		Segment3D
//!@brief	3D空間で線分を定義します
//!@brief	[始点]と[終点]や[始点]と[方向ベクトル]で表す
//----------------------------------------------------------------------------
class Segment3D
{
public:
	//!@brief	コンストラクタ
	Segment3D();
	//!@brief	コンストラクタ
	//!@param[in]	beginPoint	始点
	//!@param[in]	vector	方向ベクトル
	Segment3D(const Point3D& beginPoint, const Math::Vector3& vector);
	//!@brief	コンストラクタ
	//!@param[in]	beginPoint	始点
	//!@param[in]	endPoint	終点
	Segment3D(const Point3D& beginPoint, const Point3D& endPoint);
public:
	//!@brief	始点の取得
	//!@return	始点(Point3D)
	const Point3D&	GetBeginPoint() const;
	//!@brief	終点の取得
	//!@return	終点(Point3D)
	const Point3D&	GetEndPoint() const;
	//!@brief	方向ベクトルの取得
	//!@return	方向ベクトル(Math::Vector3)
	const Math::Vector3&	GetVector() const;
private:
	Line3D	line;
};