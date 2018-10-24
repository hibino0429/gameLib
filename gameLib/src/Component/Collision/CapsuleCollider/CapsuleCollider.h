#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/CollisionData/CollisionData.h"



//!@class		Segment
class Segment
{
public:
	//!@brief	コンストラクタ
	Segment()
	{
		data.beginPos = Math::Vector3(0, 0, 0);
		data.endPos = Math::Vector3(0, 1, 0);
	}
	//!@brief	コンストラクタ
	//!@param[in]	beginPos	始点
	//!@param[in]	endPos		終点
	Segment(const Math::Vector3& beginPos, const Math::Vector3& endPos)
	{
		data.beginPos = beginPos;
		data.endPos = endPos;
	}
public:
	//!@brief	始点の取得
	const Math::Vector3&	GetBeginPos() const
	{
		return data.beginPos;
	}
	//!@brief	終点の取得
	const Math::Vector3&	GetEndPos() const
	{
		return data.endPos;
	}
	//!@brief	始点の設定
	void	SetBeginPos(const Math::Vector3& beginPos)
	{
		data.beginPos = beginPos;
	}
	//!@brief	終点の設定
	void	SetEndPos(const Math::Vector3& endPos)
	{
		data.endPos = endPos;
	}
	//!@brief	点までの距離の2乗の取得
	//!@param[in]	pos	座標点
	//!@note	線分の端点A,B、点Cとする
	//!@note	1:ABベクトルとACベクトルの内積が負なら、点Aが点Cの最近傍
	//!@note	2:BAベクトルとBCベクトルの内積が負なら、点Bが点Cの最近傍
	//!@note	3: 1,2に該当しないなら、点Cの射影がACの内側に存在するので、その点が最近傍
	const float GetPointDistance(const Math::Vector3& pos)
	{
		const float epsilon = 1.0e-5f;	//誤差の値
		Math::Vector3 segmentSub;
		Math::Vector3 segmentPoint;
		Math::Vector3 projPos;

		//線分の始点から終点ベクトル
		segmentSub = data.endPos - data.beginPos;
		//線分の始点から指定の点へのベクトル
		segmentPoint = pos - data.beginPos;
		//2つのベクトルの内積が負なら、線分の始点が最近傍
		if (Math::Dot3D(segmentSub, segmentPoint) < epsilon)
		{
			return Math::Dot3D(segmentPoint, segmentPoint);
		}
		//点から線分の終点へのベクトル
		segmentPoint = pos - data.endPos;
		//2つのベクトルの内積が負なら、線分の始点が最近傍
		if (Math::Dot3D(segmentSub, segmentPoint) < epsilon)
		{
			return Math::Dot3D(segmentPoint, segmentPoint);
		}
		//どちらも該当しない場合、線分上に落として投影された射影が最近傍
		//([ sin使用 ]して求められるが、[ 外積の大きさ / 線分のベクトルの大きさ ]でも求まる)
		projPos = Math::Cross3D(segmentSub, segmentPoint);

		return Math::Dot3D(projPos, projPos) / Math::Dot3D(segmentSub, segmentSub);
	}
	//!@brief	線分と線分との距離(2乗)
	//!@param[in]	segment	対象の線分
	//!@note	1: 直線上の最接近点が両方の線分の内側に存在するとき
	//!@note	2: 直線上の再接近点が一方のみの線分の内側に存在するとき
	//!@note	3: 直線上の再接近点が両方の線分の外側に存在するとき
	const float	GetSegmentDistance(Segment& segment)
	{
		const float epsilon = 1.0e-5f;	//誤差
		Math::Vector3	distance1, distance2;
		Math::Vector3	beginVec;	//線分同士の始点ベクトル
		Math::Vector3	nearPos1, nearPos2;	//2つの線分上の最接近点
		Math::Vector3	pointVec;	//nearPos2 - nearPos1
		float	a, b, c, e, f;
		float	s, t;
		float	denom;
		float	tnom;

		distance1 = data.endPos - data.beginPos;
		distance2 = segment.GetEndPos() - segment.GetBeginPos();
		beginVec = data.beginPos - segment.GetBeginPos();
		a = Math::Dot3D(distance1, distance1);	//線分1の距離2乗
		e = Math::Dot3D(distance2, distance2);	//線分2の距離2乗

		//いずれかの線分の長さが0かのチェック
		if (a <= epsilon && e <= epsilon)
		{
			pointVec = data.beginPos - segment.GetBeginPos();
			return	Math::Dot3D(pointVec, pointVec);
		}
		//線分1の長さが0
		if (a <= epsilon)
		{
			return segment.GetPointDistance(data.beginPos);
		}
		//線分2の長さが0
		if (e <= epsilon)
		{
			return	GetPointDistance(segment.GetBeginPos());
		}

		//内積の計算
		b = Math::Dot3D(distance1, distance2);
		f = Math::Dot3D(distance1, beginVec);
		c = Math::Dot3D(distance1, beginVec);

		denom = a * e - b * e;	//常に非負
		//線分が平行でない場合、直線1上の直線2に対する最接近点を計算
		//線分1上にクランプ、そうでない場合、任意のsを選択
		if (denom != 0)
		{
			s = Math::Clamp((b * f - c * e) / denom, 0, 1);
		}
		else
		{
			s = 0;
		}
		//直線1上の最接近点を計算
		tnom = b * s + f;
		if (tnom < 0)
		{
			t = 0;
			s = Math::Clamp(-c / a, 0, 1);
		}
		else if (tnom > e)
		{
			t = 1;
			s = Math::Clamp((b - c) / a, 0, 1);
		}
		else
		{
			t = tnom / e;
		}
		nearPos1 = distance1 * s + data.beginPos;
		nearPos2 = distance2 * t + segment.GetBeginPos();
		pointVec = nearPos1 - nearPos2;

		return Math::Dot3D(pointVec, pointVec);
	}
private:
	SegmentData		data;
};


//---------------------------------------
//!@class		CapsuleCollider
//---------------------------------------
class CapsuleCollider : public Component
{
public:
	//!@brief	コンストラクタ
	CapsuleCollider();
	//!@brief	コンストラクタ
	//!@param[in]	segment	芯線
	//!@param[in]	radius	半径
	CapsuleCollider(const Segment& segment, const float radius);
public:
	//!@brief	芯線の取得
	const Segment&	GetSegment() const;
	//!@brief	半径の取得
	const float		GetRadius() const;
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
private:
	CapsuleData	data;
	Segment		segment;
};