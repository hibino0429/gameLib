#include "Line3D.h"


//!@brief	コンストラクタ
Line3D::Line3D()
	:point(0.0f,0.0f,0.0f)
	,vector(1.0f,0.0f,0.0f)
{

}
//!@brief	コンストラクタ
//!@param[in]	point	点
//!@param[in]	vector	方向ベクトル
Line3D::Line3D(const Point3D& point, const Math::Vector3& vector)
	: point(point)
	,vector(vector)
{

}

//!@brief	点上の座標を取得
//!@param[in]	t	ベクトルにかける係数
const Point3D& Line3D::GetPoint(const float t) const
{
	return point + Math::Vector3(t*vector.x,t*vector.y,t*vector.z);
}