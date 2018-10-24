#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/Line2D/Line2D.h"

//----------------------------------------------------------------------------
//!@class		Segment2D
//!@brief	線分(始点と終点がある)を定義
//!@brief	[始点]と[方向ベクトル]を持つ
//----------------------------------------------------------------------------
class Segment2D
{
public:
	//!@brief	コンストラクタ
	Segment2D();
	//!@brief	コンストラクタ
	//!@param[in]	point	始点
	//!@param[in]	dirVector	方向ベクトル(長さ込み)
	Segment2D(const Math::Vector2& point, const Math::Vector2& dirVector);
	//!@brief	コンストラクタ
	//!@param[in]	beginPoint	始点
	//!@param[in]	endPoint	終点
	//Segment2D(const Math::Vector2& beginPoint, const Math::Vector2& endPoint);
public:
	//!@brief	始点の取得
	//!@return	始点
	const Math::Vector2&	GetBeginPoint() const;
	//!@brief	終点の取得
	//!@return	終点
	const Math::Vector2&	GetEndPoint() const;
	//!brief	線分の長さを取得
	//!@return	線分の長さ
	const float		GetLength() const;
	//!@brief	線分の始点からある点までの長さを求める
	//!@param[in]	point	指定した一点
	//!@return	始点から一定の点までの長さ
	const float		GetLength(const Math::Vector2& point) const;
	//!@brief	線分の幅の長さ
	//!@return	widthを返す
	const float		GetWidth() const;
	//!@brief	線分の高さの長さ
	//!@return	heightを返す
	const float		GetHeight() const;
	//!@brief	始点のオフセット
	//!@param[in]	offsetVolume	オフセット量
	void	OffsetBeginPos(const Math::Vector2& offsetVolume);
private:
	Line2D	line;	//直線
};




//
//#include "../../src/Component/Collision/Point2D/Point2D.h"
//#include "../../src/Component/Collision/Circle2D/Circle2D.h"
//#include "../../src/Component/Collision/Triangle2D/Triangle2D.h"
//
//
////コリジョンの当たり判定
//namespace CollisionJudge
//{
//	//アルゴリズム
//	//1:線は点が隙間なく並んで形成
//	//2:検出は外積を利用します
//	//3:線上の点を始点、終点のベクトル算出(終点 - 始点)
//	//4:上のベクトルが、線の方向ベクトルと平行なら、線上にある
//	//5:平行な時,外積は = 0となる
//	bool	Point2DToLine2D(const Point2D& point, const Segment2D& segment)
//	{
//		//線分の始点から点までの長さ
//		float len = segment.GetLength(Math::Vector2(point.GetPoint().x, point.GetPoint().y));
//
//		//内積の結果
//		float dot = segment.GetWidth() * (point.GetPoint().x - segment.GetBeginPoint().x) + segment.GetHeight() * (point.GetPoint().y - segment.GetBeginPoint().y);
//		
//		if (dot != segment.GetLength() * len)
//		{
//			return false;
//		}
//		if (segment.GetLength() < len)
//		{
//			return false;
//		}
//		return true;
//	}
//
//
//	//アルゴリズム
//	//点と円
//	//1: 点が円内に含まれているか判定
//	//2: 円の半径と点までの距離が円の半径以下であれば衝突
//	bool	Point2DToCircle2D(const Point2D& point, const Circle2D& circle)
//	{
//		float xlen = point.GetPoint().x - circle.GetCenterPos().x;
//		float ylen = point.GetPoint().y - circle.GetCenterPos().y;
//
//		if (powf(xlen, 2) + powf(ylen, 2) > powf(circle.GetRadius(), 2))
//		{
//			return false;
//		}
//		return true;
//	}
//
//	//アルゴリズム
//	//円と円
//	//1: ２つの円の中心点間の距離が半径の長さより短いなら衝突
//	bool	Circle2DToCircle2D(const Circle2D& circle1, const Circle2D& circle2)
//	{
//		float xlen2 = powf(circle1.GetCenterPos().x - circle2.GetCenterPos().x,2);
//		float ylen2 = powf(circle2.GetCenterPos().y - circle2.GetCenterPos().y,2);
//
//		if (xlen2 + ylen2 > powf(circle1.GetRadius() + circle2.GetRadius(),2))
//		{
//			return false;
//		}
//		return true;
//	}
//
//	//内積の計算
//	float	Dot(const Math::Vector2& vector1, const Math::Vector2& vector2)
//	{
//		return vector1.x * vector2.x + vector1.y * vector2.y;
//	}
//	//外積の計算
//	float	Cross(const Math::Vector2& vector1, const Math::Vector2& vector2)
//	{
//		return vector1.x * vector2.y - vector1.y - vector2.x;
//	}
//
//	//線分と線分
//	//アルゴリズム
//	bool	Segment2DToSegment2D(const Segment2D& segment1, const Segment2D& segment2)
//	{
//		//線分の長さ
//		float	length = segment2.GetLength() - segment1.GetLength();
//		float crossV1_V2 = Cross(length, segment1.GetLength());
//		if (crossV1_V2 == 0.0f) { return false; }
//
//		float crossV_V1 = Cross(length, segment1.GetLength());
//		float crossV_V2 = Cross(length, segment2.GetLength());
//
//		float t1 = crossV_V2 / crossV1_V2;
//		float t2 = crossV_V1 / crossV1_V2;
//
//		const float eps = 0.00001f;
//		if (t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1)
//		{
//			return false;
//		}
//		return true;
//	}
//
//	//円とレイの衝突点
//	//1:円の中心点とレイとの距離を求める
//	//2:衝突していることと衝突店をいっぺんに求めてしまおう
//	bool	Circle2DToSegment2D(const Circle2D& circle, Segment2D& segment)
//	{
//		//半径のマイナスはエラー(半径のゼロは許容範囲)
//		if (circle.GetRadius() < 0.0f) { return false; }
//		//レイの方向ベクトルがない
//		if (segment.GetWidth() == 0.0f && segment.GetHeight() == 0.0f) { return false; }
//
//		//円の中心点が原点になるように始点をオフセット
//		segment.OffsetBeginPos(circle.GetCenterPos());
//
//		//レイの方向ベクトルを正規化
//		segment.Normalize();
//
//		//係数tを算出
//		float dotPos_Vec = segment.GetBeginPoint().x * segment.GetWidth() + segment.GetEndPoint().x * segment.GetHeight();
//		float dotPos_Pos = powf(segment.GetBeginPoint().x, 2) + powf(segment.GetBeginPoint().y, 2);
//		float s = dotPos_Vec * dotPos_Vec - dotPos_Pos + circle.GetRadius() * circle.GetRadius();
//		if (fabsf(s) < 0.00001f)
//		{
//			s = 0.0f;	//誤差の修正
//		}
//		if (s < 0.0f) { return false; }
//
//		float sq = sqrtf(s);
//		float t1 = -dotPos_Vec - sq;
//		float t2 = -dotPos_Pos + sq;
//
//		//t1またはt2がマイナスなら始点が円内にめり込んでいるため、エラー
//		if (t1 < 0.0f || t2 < 0.0f) { return false; }
//
//		//衝突座標の出力
//
//		return true;
//	}
//
//
//	//三角形同士の当たり判定
//	bool	Triangle2DToTriangle2D(const Triangle2D& triangle1, const Triangle2D& triangle2)
//	{
//		const int other[] = { 1,2,0 };
//		const Triangle2D*	triangle[] = { &triangle1,&triangle2,&triangle1 };
//
//		for (int t = 0; t < 2; ++t)
//		{
//			const Triangle2D& ta = *triangle[t];
//			const Triangle2D& tb = *triangle[t + 1];
//
//			for (int i = 0; i < 3; ++i)
//			{
//				//A側から分離軸の垂直線Lを算出
//				const Math::Vector2& vec = ta.GetVector(i);
//				const Math::Vector2 sepVec(vec.y, -vec.x);
//
//				//AをLに投影
//				float s1min = Dot(sepVec, ta.GetPoint(i));
//				float s1max = Dot(sepVec, ta.GetPoint(other[i]));
//				if (s1min > s1max)
//				{
//					float tmp = s1min;
//					s1min = s1max;
//					s1max = tmp;
//				}
//
//				//BをLに投影
//				float s2min = Dot(sepVec, tb.GetPoint(0));
//				float s2max = Dot(sepVec, tb.GetPoint(1));
//				if (s2min > s2max)
//				{
//					float tmp = s2min;
//					s2min = s2max;
//					s2max = tmp;
//				}
//				float d3 = Dot(sepVec, tb.GetPoint(2));
//				if (d3 < s2min)
//				{
//					s2min = d3;
//				}
//				else if (d3 > s2max)
//				{
//					s2max = d3;
//				}
//				//分離軸判定
//				if (
//					(s2min <= s1min && s1min <= s2max) ||
//					(s2min <= s2max && s1max <= s2max) ||
//					(s1min <= s2min && s2min <= s1max) ||
//					(s1min <= s2max && s2max <= s1max) 
//				   )
//				{
//					continue;	//影が重なった
//				}
//				//分離軸発見したため、衝突していない
//				return false;
//			}
//		}
//		return true;
//	}
//}