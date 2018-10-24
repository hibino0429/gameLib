#include "Point2D.h"

//!@brief	コンストラクタ
Point2D::Point2D()
	: point(Math::Vector2(0,0))
	, permissible(0.01f)
{

}
//!@brief	コンストラクタ
//!@param[in]	point	点
Point2D::Point2D(const Math::Vector2& point)
	: point(point)
	, permissible(0.01f)
{

}

//!@brief	点の取得
//!@return	点
const Math::Vector2&	Point2D::GetPoint() const
{
	return point;
}

//!@brief	点と点の当たり判定
//!@param[in]	targetPoint	相手側の点
//!@return	true: 衝突 false: 衝突していない
bool	Point2D::Hit(const Point2D& targetPoint)
{
	if (fabsf(point.x - targetPoint.GetPoint().x) < permissible)
	{
		if (fabsf(point.y - targetPoint.GetPoint().y < permissible))
		{
			return true;
		}
	}
	return false;
}