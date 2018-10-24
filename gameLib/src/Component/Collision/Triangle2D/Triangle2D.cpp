#include "Triangle2D.h"

//!@brief	コンストラクタ
Triangle2D::Triangle2D()
{
	for (int i = 0; i < 3; ++i)
	{
		point[i] = Math::Vector2(0.0f, 0.0f);
	}
}
//!@brief	コンストラクタ
//!@param[in]	point1	点1
//!@param[in]	point2	点2
//!@param[in]	point3	点3
Triangle2D::Triangle2D(const Math::Vector2& point1, const Math::Vector2& point2, const Math::Vector2& point3)
{
	point[0] = point1;
	point[1] = point2;
	point[2] = point3;
}

//!@brief	辺の長さを取得
//!@param[in]	vectorNo	ベクトルNo
//!@return	辺の長さ
const float	Triangle2D::GetLength(int vectorNo) const
{
	return point[vectorNo].Length();
}
//!@brief	辺ベクトル(非正規化)を取得
//!@param[in]	vectorNo	ベクトルNo
//!@return	辺ベクトル
const Math::Vector2&	Triangle2D::GetVector(int vectorNo) const
{
	int id[] = { 1,2,0,1 };
	return point[id[vectorNo + 1]] - point[id[vectorNo]];
}
//!@brief	頂点の取得
//!@param[in]	pointNo	頂点番号
const Math::Vector2&	Triangle2D::GetPoint(int pointNo) const
{
	return point[pointNo];
}