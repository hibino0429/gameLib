#include "Segment2D.h"

//!@brief	コンストラクタ
Segment2D::Segment2D()
	: line()
{

}
//!@brief	コンストラクタ
//!@param[in]	point	始点
//!@param[in]	dirVector	方向ベクトル(長さ込み)
Segment2D::Segment2D(const Math::Vector2& point, const Math::Vector2& dirVector)
	: line(point,dirVector)
{

}
//!@brief	コンストラクタ
//!@param[in]	beginPoint	始点
//!@param[in]	endPoint	終点
//Segment2D::Segment2D(const Math::Vector2& beginPoint, const Math::Vector2& endPoint)
//	: line(beginPoint,endPoint - beginPoint)
//{
//
//}

//!@brief	始点の取得
//!@return	始点
const Math::Vector2&	Segment2D::GetBeginPoint() const
{
	return line.GetPoint(0.0f);
}
//!@brief	終点の取得
//!@return	終点
const Math::Vector2&	Segment2D::GetEndPoint() const
{
	return line.GetPoint(1.0f);
}
//!brief	線分の長さを取得
//!@return	線分の長さ
const float		Segment2D::GetLength() const
{
	return (line.GetPoint(1.0f) - line.GetPoint(0.0f)).Length();
}
//!@brief	線分の始点からある点までの長さを求める
//!@param[in]	point	指定した一点
//!@return	始点から一定の点までの長さ
const float		Segment2D::GetLength(const Math::Vector2& point) const
{
	return (point - line.GetPoint(0.0f)).Length();
}
//!@brief	線分の幅の長さ
//!@return	widthを返す
const float		Segment2D::GetWidth() const
{
	return line.GetPoint(1.0f).x - line.GetPoint(0.0f).x;
}
//!@brief	線分の高さの長さ
//!@return	heightを返す
const float		Segment2D::GetHeight() const
{
	return line.GetPoint(1.0f).y - line.GetPoint(0.0f).y;
}
//!@brief	始点のオフセット
//!@param[in]	offsetVolume	オフセット量
void	Segment2D::OffsetBeginPos(const Math::Vector2& offsetVolume)
{
	//未実装
}