#include "Segment3D.h"

//!@brief	コンストラクタ
Segment3D::Segment3D()
	:line(Point3D(0.0f,0.0f,0.0f),Math::Vector3(1.0f,0.0f,0.0f))
{

}
//!@brief	コンストラクタ
//!@param[in]	beginPoint	始点
//!@param[in]	vector	方向ベクトル
Segment3D::Segment3D(const Point3D& beginPoint, const Math::Vector3& vector)
	: line(beginPoint,vector)
{

}
//!@brief	コンストラクタ
//!@param[in]	beginPoint	始点
//!@param[in]	endPoint	終点
Segment3D::Segment3D(const Point3D& beginPoint, const Point3D& endPoint)
	: line(beginPoint,endPoint-beginPoint)
{

}

//!@brief	始点の取得
//!@return	始点(Point3D)
const Point3D&	Segment3D::GetBeginPoint() const
{
	return line.GetPoint(0.0f);
}
//!@brief	終点の取得
//!@return	終点(Point3D)
const Point3D&	Segment3D::GetEndPoint() const
{
	return line.GetPoint(1.0f);
}
//!@brief	方向ベクトルの取得
//!@return	方向ベクトル(Math::Vector3)
const Math::Vector3&	Segment3D::GetVector() const
{
	return line.GetPoint(1.0f) - line.GetPoint(0.0f);
}