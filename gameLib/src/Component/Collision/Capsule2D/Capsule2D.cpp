#include "Capsule2D.h"

//!@brief	コンストラクタ
Capsule2D::Capsule2D()
	: segment()
	, radius(0.5f)
{

}
//!@brief	コンストラクタ
//!@param[in]	segment	線分
//!@param[in]	radius	半径
Capsule2D::Capsule2D(const Segment2D& segment, const float radius)
	: segment(segment)
	, radius(radius)
{

}
//!@brief	コンストラクタ
//!@param[in]	beginPoint	始点
//!@param[in]	endPoint	終点
//!@param[in]	radius	半径
Capsule2D::Capsule2D(const Math::Vector2& beginPoint, const Math::Vector2& endPoint, const float radius)
	: segment(beginPoint, endPoint - beginPoint)
	, radius(radius)
{

}