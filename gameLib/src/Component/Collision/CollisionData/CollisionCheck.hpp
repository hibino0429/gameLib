#pragma once
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/Component/Collision/SphereCollider/SphereCollider.h"
#include "../../src/Component/Collision/CapsuleCollider/CapsuleCollider.h"
#include "../../src/Component/Collision/BoxCollider/BoxCollider.h"
#include "../../src/Component/Collision/AABB/AABB.h"
#include "../../src/Component/Collision/Ray/Ray.h"
#include "../../src/Component/Collision/Plane/Plane.h"
#include <amp.h>
#include <algorithm>

struct CollisionWorld
{
	//!@brief	球と球との当たり判定
	//!@return	true:当たっている  false:当たっていない
	static bool	CheckSphereToSphere(const SphereCollider& sphere1, const SphereCollider& sphere2)
	{
		//球と球との差分
		//sub.Distance(const Math::Vector3& pos);
		float sub = Math::VectorLength(sphere1.GetCenterPosition(), sphere2.GetCenterPosition());
		//三平方の定理で、ベクトルの長さを計算
		float	distance = sub * sub;
		//半径の和
		float sumRadius = sphere1.GetRadius() + sphere2.GetRadius();
		float	sumRadius2 = sumRadius * sumRadius;
		//距離の半径の和がより大きいなら当たっていない
		if (distance > sumRadius2)
		{
			return false;
		}
		return true;
	}
	//!@brief	球とカプセルとの当たり判定
	static bool	CheckSphereToCapsule(const SphereCollider& sphere,const CapsuleCollider& capsule)
	{
		//球の中心とカプセルの線分の距離(2乗)計算
		Segment seg = capsule.GetSegment();
		float distance2 = seg.GetPointDistance(sphere.GetCenterPosition());
		
		//距離(2乗)が半径の和(2乗)より小さければ当たっている
		float radius = sphere.GetRadius() + capsule.GetRadius();
		if (distance2 > radius * radius)
		{
			return false;
		}
		return true;
	}
	//!@brief	カプセルとカプセルとの当たり判定
	static bool	CheckCapsuleToCapsule(const CapsuleCollider& capsule1, const CapsuleCollider& capsule2)
	{
		//球の中心とカプセルの中心(2乗)計算
		Segment seg = capsule1.GetSegment();
		Segment seg2 = capsule2.GetSegment();
		float distance2 = seg.GetSegmentDistance(seg2);

		//半径の和(2乗)の計算
		float radiusSum = capsule1.GetRadius() + capsule2.GetRadius();
		float radius2 = radiusSum * radiusSum;

		//距離(2乗)が半径の和(2乗)より大きければ、当たり
		if (distance2 > radius2)
		{
			return false;
		}
		return true;
	}

	//!@brief	AABB同士の当たり判定
	//!@note	衝突条件
	//!@note	aabb1の右側がaabb2の左側より大きい　かつ
	//!@note	aabb1の左側がaabb2の右側より小さい　かつ
	//!@note	aabb1の上側がaabb2の下側より大きい　かつ
	//!@note	aabb1の下側がaabb2の上側より小さい  なら衝突
	bool	CheckAABBToAABB(AABB& aabb1, AABB& aabb2)
	{
		Segment seg(aabb2.GetLeftUpFrontPos(),aabb2.GetLeftUpBackPos());
		Segment seg2(aabb2.GetLeftUpBackPos(), aabb2.GetRightUpBackPos());
		Segment seg3(aabb2.GetRightUpBackPos(), aabb2.GetRightUpFrontPos());
		Segment seg4(aabb2.GetRightUpFrontPos(), aabb2.GetLeftUpFrontPos());
		Segment seg5(aabb2.GetLeftUpBackPos(), aabb2.GetLeftDownBackPos());
		Segment seg6(aabb2.GetRightUpBackPos(), aabb2.GetRightDownBackPos());
		Segment seg7(aabb2.GetRightUpFrontPos(), aabb2.GetRightDownFrontPos());
		Segment seg8(aabb2.GetLeftUpFrontPos(), aabb2.GetLeftDownFrontPos());
		Segment seg9(aabb2.GetLeftUpFrontPos(), aabb2.GetLeftDownBackPos());
		Segment seg10(aabb2.GetLeftDownBackPos(), aabb2.GetRightDownBackPos());
		Segment seg11(aabb2.GetRightDownBackPos(), aabb2.GetRightDownFrontPos());
		Segment seg12(aabb2.GetRightDownFrontPos(), aabb2.GetLeftDownFrontPos());
		if (!aabb1.HitSegment(seg)) { return false; }
		if (!aabb1.HitSegment(seg2)) { return false; }
		if (!aabb1.HitSegment(seg3)) { return false; }
		if (!aabb1.HitSegment(seg4)) { return false; }
		if (!aabb1.HitSegment(seg5)) { return false; }
		if (!aabb1.HitSegment(seg6)) { return false; }
		if (!aabb1.HitSegment(seg7)) { return false; }
		if (!aabb1.HitSegment(seg8)) { return false; }
		if (!aabb1.HitSegment(seg9)) { return false; }
		if (!aabb1.HitSegment(seg10)) { return false; }
		if (!aabb1.HitSegment(seg11)) { return false; }
		if (!aabb1.HitSegment(seg12)) { return false; }
		return true;
	}

	//!@brief	OBB同士の当たり判定
	static bool	CheckOBBToOBB(const BoxCollider& obb1, const BoxCollider& obb2)
	{
		//各方向のベクトルの確保
		Math::Vector3	normalAe1 = obb1.GetDirect(0), Ae1 = normalAe1 * obb1.GetLength(0);
		Math::Vector3	normalAe2 = obb1.GetDirect(1), Ae2 = normalAe2 * obb1.GetLength(1);
		Math::Vector3	normalAe3 = obb1.GetDirect(2), Ae3 = normalAe3 * obb1.GetLength(2);
		Math::Vector3	normalBe1 = obb2.GetDirect(0), Be1 = normalBe1 * obb2.GetLength(0);
		Math::Vector3	normalBe2 = obb2.GetDirect(1), Be2 = normalBe2 * obb2.GetLength(1);
		Math::Vector3	normalBe3 = obb2.GetDirect(2), Be3 = normalBe3 * obb2.GetLength(2);
		//中心座標同士の距離
		Math::Vector3	interval = obb1.GetCenter() - obb2.GetCenter();

		//分離軸 : Ae1
		float	rA = Ae1.Length();
		float	rB = Math::LengthSegmentOnSeparateAxis(normalAe1, normalBe1, Be2, Be3);
		float	len = fabsf(Math::Dot3D(interval, normalAe1));
		//中心点座標の距離よりも半投影線分の長さの合計が小さいなら、衝突してない
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : Ae2
		rA = Ae2.Length();
		rB = Math::LengthSegmentOnSeparateAxis(normalAe2, Be1, Be2, Be3);
		len = fabs(Math::Dot3D(interval, normalAe2));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : Ae3
		rA = Ae3.Length();
		rB = Math::LengthSegmentOnSeparateAxis(normalAe3, Be1, Be2, Be3);
		len = fabs(Math::Dot3D(interval, normalAe3));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : Be1
		rA = Math::LengthSegmentOnSeparateAxis(normalBe1, Ae1, Ae2, Ae3);
		rB = Be1.Length();
		len = fabs(Math::Dot3D(interval, normalBe1));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : Be2
		rA = Math::LengthSegmentOnSeparateAxis(normalBe2, Ae1, Ae2, Ae3);
		rB = Be2.Length();
		len = fabs(Math::Dot3D(interval, normalBe2));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : Be3
		rA = Math::LengthSegmentOnSeparateAxis(normalBe3, Ae1, Ae2, Ae3);
		rB = Be3.Length();
		len = fabs(Math::Dot3D(interval, normalBe3));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : C11
		Math::Vector3	cross;
		cross = Math::Cross3D(normalAe1, normalBe1);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae2, Ae3);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be2, Be3);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : C12
		cross = Math::Cross3D(cross, normalAe1, normalBe2);
		rA = LengthSegmentOnSeparateAxis(cross, Ae2, Ae3);
		rB = LengthSegmentOnSeparateAxis(cross, Be1, Be3);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : C13
		cross = Math::Cross3D(cross, normalAe1, normalBe3);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae2, Ae3);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be1, Be2);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : C21
		cross = Math::Cross3D(cross, normalAe2, normalBe1);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae1, Ae3);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be2, Be3);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : C22
		cross = Math::Cross3D(cross, normalAe2, normalBe2);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae1, Ae3);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be1, Be3);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : C23
		cross = Math::Cross3D(cross, normalAe2, normalBe3);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae1, Ae3);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be1, Be2);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : C31
		cross = Math::Cross3D(cross, normalAe3, normalBe1);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae1, Ae2);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be2, Be3);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : C32
		cross = Math::Cross3D(cross, normalAe3, normalBe2);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae1, Ae2);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be1, Be3);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//分離軸 : C33
		cross = Math::Cross3D(cross, normalAe3, normalBe3);
		rA = Math::LengthSegmentOnSeparateAxis(cross, Ae1, Ae2);
		rB = Math::LengthSegmentOnSeparateAxis(cross, Be1, Be2);
		len = fabs(Math::Dot3D(interval, cross));
		if (len > rA + rB)
		{
			return false;
		}
		//分離平面が存在しないため衝突
		return true;
	}
	
	//!@brief	ボックス同士の当たり判定
	//!@param[in]	box1	ボックス1
	//!@param[in]	box2	ボックス2
	static bool	CheckBoxToBox(const BoxCollider& box1, const BoxCollider& box2)
	{
		if (box1.GetMinPos().x > box2.GetMaxPos().x) { return false; }
		if (box1.GetMaxPos().x < box2.GetMinPos().x) { return false; }
		if (box1.GetMinPos().y > box2.GetMaxPos().y) { return false; }
		if (box1.GetMaxPos().y < box2.GetMinPos().y) { return false; }
		if (box1.GetMinPos().z > box2.GetMaxPos().z) { return false; }
		if (box1.GetMaxPos().z < box2.GetMinPos().z) { return false; }
		return true;

		Math::Vector3	v;		//分離軸 v
		float	box1Vertex;		//ボックス1の頂点 |v|・a
		float	box2Vertex;		//ボックス2の頂点 |v * Bt|・b
		float	box2Center;		//ボックス2の中心座標 |v ・c|
		//平行移動
		Math::Vector3	trans;
		//AのX軸
		v = Math::Vector3(1, 0, 0);
		box1Vertex = Math::Dot3D(AbsVector3(v),box1.GetSize());
		box2Center = fabsf(Math::Dot3D(v, trans));
		//box2Vertex = 
		//Aのx軸
		//Math::Vector3	v;	//分離軸
	}
	static Math::Vector3	AbsVector3(const Math::Vector3& vec3)
	{
		Math::Vector3 vec;
		vec.x = fabsf(vec3.x);
		vec.y = fabsf(vec3.y);
		vec.z = fabsf(vec3.z);
		return vec;
	}
	//!@brief	レイと球との当たり判定
	//!@param[in]	ray	レイ
	//!@param[in]	sphere	球
	//!@param[in]	hitPos	衝突座標(取得用)
	static bool	CheckRayToSphere(const Ray& ray, const SphereCollider& sphere,Math::Vector3* hitPos = nullptr)
	{
		float pos2 = std::powf(ray.GetBeginPos().x, 2) + std::powf(ray.GetBeginPos().y, 2) + std::powf(ray.GetBeginPos().x, 2);
		float v2 = std::powf(ray.GetDirVec().x, 2) + std::powf(ray.GetDirVec().y, 2) + std::powf(ray.GetDirVec().z, 2);
		float posDotDir = Math::Dot3D(ray.GetBeginPos(), ray.GetDirVec());
		float sub2 = pos2 - std::powf(sphere.GetRadius(), 2.0f);
		float d = std::powf(posDotDir, 2.0f) - v2 * (pos2 - std::powf(sphere.GetRadius(), 2.0f));

		if (d < 0.0f) { return false; }

		if (!Utility::CheckNull(hitPos))
		{
			//交点の検出
			float t = -posDotDir - std::sqrtf(d);
			*hitPos = ray.GetBeginPos() + (ray.GetDirVec() * t);
		}
		return true;
	}
	//!@brief	レイと平面との当たり判定
	//!@param[in]	ray	レイ
	//!@param[in]	plane	平面
	//!@param[in]	hitPos	衝突座標(取得用)
	static bool	CheckRayToPlane(const Ray& ray, const Plane& plane,Math::Vector3* hitPos = nullptr)
	{
		//レイの始点と平面との距離を算出
		float length = plane.GetLength(ray.GetBeginPos());
		//レイの方向ベクトルの2乗を算出
		float rayVec2 = ray.GetDirVec().x * ray.GetDirVec().x + ray.GetDirVec().y * ray.GetDirVec().y + ray.GetDirVec().z * ray.GetDirVec().z;
		//距離を比較し平面に届くかチェック
		if (rayVec2 < length * length) { return false; }
		
		float raySqVec2 = sqrtf(rayVec2);
		//cosを利用して内積を求める
		Math::Vector3	vec = ray.GetDirVec() * (1.0f / raySqVec2);
		//レイのベクトルを正規化
		//方向ベクトル(正規化)と平面法線の反転
		float	dot = Math::Dot3D(vec, -plane.GetNormal());
		
		//線分が平面に届く距離を算出し、平面に届くか判断
		float planeLen = length / dot;
		if (planeLen > raySqVec2) { return false; }

		//平面との交点を算出
		if (!Utility::CheckNull(hitPos))
		{
			*hitPos = ray.GetBeginPos() + (vec * planeLen);
		}
		return true;
	}
	//!@brief	球と平面との当たり判定
	//!@param[in]	sphere	球
	//!@param[in]	plane	平面
	//!@param[in]	hitVec	めり込み量(取得用)
	static bool	CheckSphereToPlane(const SphereCollider& sphere, const Plane& plane,Math::Vector3* hitVec = nullptr)
	{
		//平面と球との中心距離
		float length = plane.GetLength(sphere.GetCenterPosition());
		if (length > sphere.GetRadius()) { return false; }

		//めり込み量
		if (!Utility::CheckNull(hitVec))
		{
			length = sphere.GetRadius() - length;
			*hitVec = Math::Vector3(plane.GetA() * length + plane.GetB() * length + plane.GetC() * length);
		}
		return true;
	}
	//!@brief	平面と平面との当たり判定
	//!@param[in]	plane1	平面1
	//!@param[in]	plane2	平面2
	static bool	CheckPlaneToPlane(const Plane& plane1, const Plane& plane2)
	{
		//平面の法線を利用し、平面が平行かをチェック
		float dot = (plane1.GetA() * plane2.GetA()) + (plane1.GetB() * plane2.GetB()) + (plane1.GetC() * plane2.GetC());
		if ((dot >= 1.0f) || (dot <= -1.0f)) { return false; }

		//if (ray) { return true; }
		//交差線分を必要に応じて作成
		//外積を利用して交差する線分ベクトルを作成
		Math::Vector3 vec = Math::Cross3D(Math::Vector3(plane1.GetA(), plane1.GetB(), plane1.GetC()), Math::Vector3(plane2.GetA(), plane2.GetB(), plane2.GetC()));
		//交差線分の始点を算出
		Math::Vector3	beginPos;
		if (vec.z != 0.0f)
		{
			beginPos = Math::Vector3(
				(plane2.GetB() * plane1.GetD() - plane1.GetB() * plane2.GetD()) / vec.z,
				(plane1.GetA() * plane2.GetD() - plane2.GetA() * plane1.GetD()) / vec.z,
				0.0f
			);
		}
		else if (vec.y != 0.0f)
		{
			beginPos = Math::Vector3(
				(plane2.GetC() * plane1.GetD() - plane1.GetC() * plane2.GetD()) / vec.y,
				0.0f,
				(plane1.GetA() * plane2.GetD() - plane2.GetA() * plane1.GetD()) / vec.y
			);
		}
		else
		{
			beginPos = Math::Vector3(
				0.0f,
				(plane1.GetC() * plane2.GetD() - plane2.GetC() * plane1.GetD()) / vec.x,
				(plane2.GetB() * plane1.GetD() - plane1.GetB() * plane2.GetD()) / vec.x
			);
		}
		//線分の設定
		//Ray* ray = new Ray(beginPos, vec);
		return true;
	}
	//ボックスと球との当たり判定
	static bool		CheckBoxToSphere(const BoxCollider& box, const SphereCollider& sphere)
	{
		//クランプ関数を決める
		Math::Vector3	boxSurfacePoint;
		boxSurfacePoint.x = Clamp(sphere.GetCenterPosition().x, -box.GetSize().x, box.GetSize().x);
		boxSurfacePoint.y = Clamp(sphere.GetCenterPosition().y, -box.GetSize().y, box.GetSize().y);
		boxSurfacePoint.z = Clamp(sphere.GetCenterPosition().z, -box.GetSize().z, box.GetSize().z);

		Math::Vector3	sub = boxSurfacePoint - sphere.GetCenterPosition();
		float distance2 = std::powf(sub.x, 2.0f) + std::powf(sub.y, 2.0f) + std::powf(sub.z, 2.0f);
		if (distance2 > sphere.GetRadius() * sphere.GetRadius())
		{
			return false;
		}
		return true;
	}
	static float Clamp(float value, float min, float max)
	{
		if (value < min)
		{
			return min;
		}
		else if (value > max)
		{
			return max;
		}
		return value;
	}
};