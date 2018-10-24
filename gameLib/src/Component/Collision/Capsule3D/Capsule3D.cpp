#include "Capsule3D.h"


//!@brief	コンストラクタ
Capsule3D::Capsule3D()
	: radius(0.5f)
{

}
//!@brief	コンストラクタ
//!@param[in]	segment	線分
//!@param[in]	radius	半径
Capsule3D::Capsule3D(const Segment3D& segment, const float radius)
	: segment(segment)
	, radius(radius)
{

}
//!@brief	コンストラクタ
//!@param[in]	point1	点1
//!@param[in]	point2	点2
//!@param[in]	radius	半径
Capsule3D::Capsule3D(const Point3D& point1, const Point3D& point2, const float radius)
	: segment(point1,point2)
	, radius(radius)
{

}

//!@brief	線分の取得
//!@return	線分
const Segment3D&	Capsule3D::GetSegment() const
{
	return segment;
}
//!@brief	半径の取得
//!@return	半径
const float&	Capsule3D::GetRadius() const
{
	return radius;
}