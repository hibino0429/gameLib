#include "Point3D.h"

//!@brief	コンストラクタ
Point3D::Point3D()
	: Math::Vector3(0.0f,0.0f,0.0f)
{

}
//!@brief	コンストラクタ
//!@param[in]	point	点
Point3D::Point3D(const Math::Vector3& point)
{
	x = point.x;
	y = point.y;
	z = point.z;
}
//!@brief	コンストラクタ
//!@param[in]	x	座標x
//!@param[in]	y	座標y
//!@param[in]	z	座標z
Point3D::Point3D(const float x, const float y, const float z)
	: Math::Vector3(x,y,z)
{
	
}

//!@brief	点座標の取得
//!@return	点の座標
const Math::Vector3&	Point3D::GetPointPos() const
{
	return *this;
}