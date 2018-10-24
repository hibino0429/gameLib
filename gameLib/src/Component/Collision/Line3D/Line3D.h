#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/Point3D/Point3D.h"

//----------------------------------------------------------------------------
//!@class		Line3D
//!@brief	3D空間での直線を定義します
//!@brief	[直線上の一点]と[方向ベクトル]で表します
//----------------------------------------------------------------------------
class Line3D
{
public:
	//!@brief	コンストラクタ
	Line3D();
	//!@brief	コンストラクタ
	//!@param[in]	point	点
	//!@param[in]	vector	方向ベクトル
	Line3D(const Point3D& point, const Math::Vector3& vector);
public:
	//!@brief	点上の座標を取得
	//!@param[in]	t	ベクトルにかける係数
	const Point3D& GetPoint(const float t) const;
private:
	Point3D			point;
	Math::Vector3	vector;
};







//#include "../../src/Component/Collision/Segment3D/Segment3D.h"
//#include "../../src/Component/Collision/Plane/Plane.h"
//#include "../../src/Component/Collision/Sphere/Sphere.h"
//#include "../../src/Component/Collision/AABB/AABB.h"
//
//
////コリジョン３Dの当たり判定
//namespace CollisionJudge
//{
//	//点と線
//	bool	Point3DToSegment3D(const Point3D& point, const Segment3D& segment)
//	{
//		//平行なベクトルから求めた[法線ベクトル]は0ベクトルになる
//		//segmentの始点から衝突点へ向かうベクトルの算出
//		//そのベクトルの大きさが線分の長さより小さいなら衝突
//		Math::Vector3 vec = segment.GetBeginPoint() - point;
//		Math::Vector3 cross = Cross3D(vec, segment.GetVector());
//		if (cross.x != 0 || cross.y != 0 || cross.z != 0)
//		{
//			return false;
//		}
//		if (vec.Length() > cross.Length())
//		{
//			return false;
//		}
//		return true;
//	}
//
//	//線と線
//	bool	Segment3DToSegment3D(const Segment3D& segment1, const Segment3D& segment2)
//	{
//		//平面にある平行でない線は必ず交わる
//
//		//1:2辺が同じ平面に乗っているかチェック
//		//その際に、2つの線ベクトルの外積の法線ベクトルを調べる
//		Math::Vector3 cross = Math::Cross3D(segment1.GetVector(), segment2.GetVector());
//
//		//2:線分1上の点から線分2上の点まで伸ばしたベクトルの算出
//		Math::Vector3 vec = segment1.GetBeginPoint() - segment2.GetBeginPoint();
//		Math::Vector3 normalVec = Math::Cross3D(segment1.GetVector(), vec);
//
//		//3:normalVecが0以外なら衝突を起こしていない
//		if (normalVec.Length() != 0)
//		{
//			return false;
//		}
//
//		//|n1| <= 0　なら衝突はない
//		if (cross.Length() <= 0)
//		{
//			return false;
//		}
//		//|n1*n2| == 0なら衝突
//		if (Math::Cross3D(cross, normalVec).Length() != 0)
//		{
//			return false;
//		}
//		return true;
//	}
//
//	//線分と平面
//	bool	Segment3DToPlane(const Segment3D& segment, const Plane& plane)
//	{
//		//無限に広がる平面に対して線が交わらない場合、[平面と線分が平行]
//		//平面の法線ベクトルと線のベクトルが垂直かチェック(内積0)
//		//v1・n == 0 または v・n != 0　なら衝突
//		//v1は平面上の点p0と線上の点p1のベクトル
//		Math::Vector3	vector1 = plane.GetPoint() - segment.GetBeginPoint();
//		if (Math::Dot3D(vector1, plane.GetNormal()) != 0)
//		{
//			return false;
//		}
//		if (Math::Dot3D(segment.GetVector(), plane.GetNormal()) == 0)
//		{
//			return false;
//		}
//		//線分は2点を結んだ部分線なので、平面と衝突しているなら点の一つが平面の裏と表にある
//		//法線ベクトルと線分ベクトルは面の表のどこであっても、角度は鋭角になる
//		//(v1 ・ n) * (v2 ・ n) <= 0 なら衝突
//		Math::Vector3	vector2 = plane.GetPoint() - segment.GetEndPoint();
//		if (Math::Dot3D(vector1, plane.GetNormal()) * Math::Dot3D(vector2, plane.GetNormal()) > 0)
//		{
//			return false;
//		}
//		return true;
//	}
//
//	//球と球
//	bool	SphereToSphere(const Sphere& sphere1, const Sphere& sphere2)
//	{
//		float lengthX = sphere2.GetCenterPoint().x - sphere1.GetCenterPoint().x;
//		float lengthY = sphere2.GetCenterPoint().y - sphere1.GetCenterPoint().y;
//		float lengthZ = sphere2.GetCenterPoint().z - sphere1.GetCenterPoint().z;
//		//中心同士の距離と半径の合計の比較
//		if (powf(lengthX, 2) + powf(lengthY, 2) + powf(lengthZ, 2) > powf(sphere1.GetRadius() + sphere2.GetRadius(), 2))
//		{
//			return false;
//		}
//		return true;
//	}
//
//
//	//AABBとAABB
//	bool	AABBToAABB(const AABB& aabbBox1, const AABB& aabbBox2)
//	{
//
//	}
//}