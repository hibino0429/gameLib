#include "AABB.h"

//!@brief	�R���X�g���N�^
AABB::AABB()
{
	data.minPos = Math::Vector3(0, 0, 0);
	data.maxPos = Math::Vector3(1, 1, 1);
	data.size = data.maxPos - data.minPos;
	data.centerPos = data.size / 2.0f;
}
//!@brief	�R���X�g���N�^
//!@param[in]	centerPos	���S�_
//!@param[in]	sideHalfLength	�e���̕ӂ̔����̒���
AABB::AABB(const Math::Vector3& centerPos, const Math::Vector3& sideHalfLength)
{
	data.centerPos = centerPos;
	data.minPos = data.centerPos - (sideHalfLength / 2.0f);
	data.maxPos = data.centerPos + (sideHalfLength / 2.0f);
	data.size = data.maxPos - data.minPos;
}

//!@brief	X���̕ӂ̒����̎擾
//!@return	x���̒���
const float&	AABB::GetLengthX() const
{
	return data.size.x;
}
//!@brief	Y���̕ӂ̒����̎擾
//!@return	y���̒���
const float&	AABB::GetLengthY() const
{
	return data.size.y;
}
//!@brief	Z���̕ӂ̒����̎擾
//!@return	z���̒���
const float&	AABB::GetLengthZ() const
{
	return data.size.z;
}

//!@brief	���S���W�̎擾
//!@return	���S���W(x,y,z)
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
	//���ʊi�[
	float	tMin, tMax;

	//x���̈�ł̔���
	float txMin, txMax;
	if (segment.GetEndPos().x - segment.GetBeginPos().x == 0.0f)
	{
		//�����x�N�g����0�̏ꍇ�A����
		if ((segment.GetBeginPos().x < data.minPos.x) || (segment.GetBeginPos().x > data.maxPos.x))
		{
			return false;
		}
		txMin = 0.0f;
		txMax = 1.0f;
	}
	else
	{
		//x���ł̗̈������
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

	//y���̈�ł̔���
	float	tyMin, tyMax;
	if (segment.GetEndPos().y - segment.GetBeginPos().y == 0.0f)
	{
		//�����x�N�g����0�̎��A����
		if ((segment.GetBeginPos().y < data.minPos.y) || (segment.GetBeginPos().y > data.maxPos.y))
		{
			return false;
		}
		tyMin = 0.0f;
		tyMax = 1.0f;
	}
	else
	{
		//y���ł̗̈�̌���
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
	//x����y���̗̈悪���Ԃ��Ă��Ȃ�
	if (tMin < tyMin) { tMin = tyMin; }
	if (tMax > tyMax) { tMax = tyMax; }

	//z���̈�̔���
	float	tzMin, tzMax;
	if (segment.GetEndPos().z - segment.GetBeginPos().z == 0.0f)
	{
		//����
		if ((segment.GetBeginPos().z < data.minPos.z) || (segment.GetBeginPos().z > data.maxPos.z)) { return false; }
		tzMin = 0.0f;
		tzMax = 1.0f;
	}
	else
	{
		//z���ł̗̈攻��
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
	//x,y����z���̗̈攻��
	if (tMin < tzMin) { tMin = tzMin; }
	if (tMax > tzMax) { tMax = tzMax; }

	//���ʗ̈攻��
	if ((tMin > 1.0f) || (tMax < 0.0f))
	{
		return false;
	}
	return true;
}
