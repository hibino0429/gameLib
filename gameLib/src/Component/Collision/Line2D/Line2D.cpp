#include "Line2D.h"

//!@brief	コンストラクタ
Line2D::Line2D()
	: point(0.0f,0.0f)
	, dirVector(1.0f,0.0f)
{

}
//!@brief	コンストラクタ
//!@param[in]	point		点
//!@param[in]	dirVector	方向ベクトル
Line2D::Line2D(const Math::Vector2& point, const Math::Vector2& dirVector)
	: point(point)
	, dirVector(dirVector)
{

}

//!@brief	点上の座標を取得
//!@param[in]	t	ベクトルにかける係数
//!@return	点の座標
const Math::Vector2&	Line2D::GetPoint(const float t) const
{
	return point + Math::Vector2(t * dirVector.x, t * dirVector.y);
}