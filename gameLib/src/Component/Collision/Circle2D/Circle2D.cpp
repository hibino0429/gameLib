#include "Circle2D.h"

//!@brief	コンストラクタ
Circle2D::Circle2D()
	: centerPos(0.0f,0.0f)
	, radius(0.0f)
{

}
//!@brief	コンストラクタ
//!@param[in]	centerPos	中心点
//!@param[in]	radius	半径
Circle2D::Circle2D(const Math::Vector2& centerPos, const float radius)
	: centerPos(centerPos)
	, radius(radius)
{

}
//!@brief	中心点の取得
//!@return	中心点
const Math::Vector2&	Circle2D::GetCenterPos() const
{
	return centerPos;
}
//!@brief	半径の取得
//!@return	半径
const float		Circle2D::GetRadius() const
{
	return radius;
}
//!@brief	中心点のオフセット
//!@param[in]	offsetVolume	オフセット量
void	Circle2D::OffsetCenterPos(const Math::Vector2& offsetVolume)
{
	centerPos += offsetVolume;
}