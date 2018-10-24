#include "AABB.h"

//!@brief	コンストラクタ
AABB::AABB()
{
	data.minPos = Math::Vector3(0, 0, 0);
	data.maxPos = Math::Vector3(1, 1, 1);
	data.size = data.maxPos - data.minPos;
	data.centerPos = data.size / 2.0f;
}
//!@brief	コンストラクタ
//!@param[in]	centerPos	中心点
//!@param[in]	sideHalfLength	各軸の辺の半分の長さ
AABB::AABB(const Math::Vector3& centerPos, const Math::Vector3& sideHalfLength)
{
	data.centerPos = centerPos;
	data.minPos = data.centerPos - (sideHalfLength / 2.0f);
	data.maxPos = data.centerPos + (sideHalfLength / 2.0f);
	data.size = data.maxPos - data.minPos;
}

//!@brief	X軸の辺の長さの取得
//!@return	x軸の長さ
const float&	AABB::GetLengthX() const
{
	return data.size.x;
}
//!@brief	Y軸の辺の長さの取得
//!@return	y軸の長さ
const float&	AABB::GetLengthY() const
{
	return data.size.y;
}
//!@brief	Z軸の辺の長さの取得
//!@return	z軸の長さ
const float&	AABB::GetLengthZ() const
{
	return data.size.z;
}

//!@brief	中心座標の取得
//!@return	中心座標(x,y,z)
const Math::Vector3&	AABB::GetCenterPos() const
{
	return data.centerPos;
}

const Math::Vector3 & AABB::GetLeftUpBackPos() const
{
	return data.minPos + Math::Vector3(0, data.size.y, 0);
}

const Math::Vector3 & AABB::GetLeftUpFrontPos() const
{
	return data.minPos + Math::Vector3(0, data.size.y, -data.size.z);
}

const Math::Vector3 & AABB::GetLeftDownBackPos() const
{
	return data.minPos;
}

const Math::Vector3 & AABB::GetLeftDownFrontPos() const
{
	return data.minPos + Math::Vector3(0, 0, -data.size.z);
}

const Math::Vector3 & AABB::GetRightUpBackPos() const
{
	return data.maxPos + Math::Vector3(0, 0, data.size.z);
}

const Math::Vector3 & AABB::GetRightUpFrontPos() const
{
	return data.maxPos;
}

const Math::Vector3 & AABB::GetRightDownBackPos() const
{
	return data.maxPos + Math::Vector3(0, -data.size.y, data.size.z);
}

const Math::Vector3 & AABB::GetRightDownFrontPos() const
{
	return data.maxPos + Math::Vector3(0, -data.size.y, 0);
}

bool AABB::HitSegment(Segment & segment)
{
	//結果格納
	float	tMin, tMax;

	//x軸領域での判定
	float txMin, txMax;
	if (segment.GetEndPos().x - segment.GetBeginPos().x == 0.0f)
	{
		//線分ベクトルが0の場合、特殊
		if ((segment.GetBeginPos().x < data.minPos.x) || (segment.GetBeginPos().x > data.maxPos.x))
		{
			return false;
		}
		txMin = 0.0f;
		txMax = 1.0f;
	}
	else
	{
		//x軸での領域を決定
		float t0 = (data.minPos.x - segment.GetBeginPos().x) / segment.GetEndPos().x / segment.GetBeginPos().x;
		float t1 = (data.maxPos.x - segment.GetBeginPos().x) / segment.GetEndPos().x / segment.GetBeginPos().x;
		if (t0 < t1)
		{
			txMin = t0;	
			txMax = t1;
		}
		else
		{
			txMin = t1;
			txMax = t0;
		}
		if ((txMax < 0.0f) || txMin > 1.0f) { return false; }
	}
	tMin = txMin;
	tMax = txMax;

	//y軸領域での判定
	float	tyMin, tyMax;
	if (segment.GetEndPos().y - segment.GetBeginPos().y == 0.0f)
	{
		//線分ベクトルが0の時、特殊
		if ((segment.GetBeginPos().y < data.minPos.y) || (segment.GetBeginPos().y > data.maxPos.y))
		{
			return false;
		}
		tyMin = 0.0f;
		tyMax = 1.0f;
	}
	else
	{
		//y軸での領域の決定
		float t0 = (data.minPos.y - segment.GetBeginPos().y) / segment.GetEndPos().y - segment.GetBeginPos().y;
		float t1 = (data.maxPos.y - segment.GetBeginPos().y) / segment.GetEndPos().y - segment.GetBeginPos().y;
		if (t0 < t1)
		{
			tyMin = t0;
			tyMax = t1;
		}
		else
		{
			tyMin = t1;
			tyMax = t0;
		}
		if ((tyMax < 0.0f) || (tyMin > 1.0f))
		{
			return false;
		}
	}
	if ((tMax < tyMin) || (tMin > tyMax)) { return false; }
	//x軸とy軸の領域がかぶっていない
	if (tMin < tyMin) { tMin = tyMin; }
	if (tMax > tyMax) { tMax = tyMax; }

	//z軸領域の判定
	float	tzMin, tzMax;
	if (segment.GetEndPos().z - segment.GetBeginPos().z == 0.0f)
	{
		//特殊
		if ((segment.GetBeginPos().z < data.minPos.z) || (segment.GetBeginPos().z > data.maxPos.z)) { return false; }
		tzMin = 0.0f;
		tzMax = 1.0f;
	}
	else
	{
		//z軸での領域判定
		float	t0 = (data.minPos.z - segment.GetBeginPos().z) / segment.GetEndPos().z - segment.GetBeginPos().z;
		float	t1 = (data.maxPos.z - segment.GetBeginPos().z) / segment.GetEndPos().z - segment.GetBeginPos().z;
		if (t0 < t1)
		{
			tzMin = t0;
			tzMax = t1;
		}
		else
		{
			tzMin = t1;
			tzMax = t0;
		}
		if ((tzMax < 0.0f) || (tzMin > 1.0f)) { return false; }
	}
	if ((tMax < tzMin) || (tMin > tzMax)) { return false; }
	//x,y軸とz軸の領域判定
	if (tMin < tzMin) { tMin = tzMin; }
	if (tMax > tzMax) { tMax = tzMax; }

	//共通領域判定
	if ((tMin > 1.0f) || (tMax < 0.0f))
	{
		return false;
	}
	return true;
}
