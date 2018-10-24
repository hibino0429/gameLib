#include "Sphere.h"


//!@brief	コンストラクタ
Sphere::Sphere()
	: point(0.0f,0.0f,0.0f)
	, radius(0.5f)
{

}
//!@brief	コンストラクタ
//!@param[in]	centerPos	中心点
//!@param[in]	radius	半径
Sphere::Sphere(const Point3D& centerPoint, const float radius)
	: point(centerPoint)
	, radius(radius)
{

}

//!@brief	中心点の取得
//!@return	半径(Point3D)
const Point3D&	Sphere::GetCenterPoint() const
{
	return point;
}
//!@brief	半径の取得
//!@return	半径(float)
const float		Sphere::GetRadius() const
{
	return radius;
}