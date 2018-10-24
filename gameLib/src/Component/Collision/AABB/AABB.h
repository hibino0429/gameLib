#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/CollisionData/CollisionData.h"
#include "../../src/Component/Collision/CapsuleCollider/CapsuleCollider.h"



//----------------------------------------------------------------------------
//!@class		AABB
//!@brief	���[���h��Ԃ�XYZ���ɑ΂��Ċm�ς����s�Ȓ����̂̒�`
//!@brief	[���S�_]��[�e���̕ӂ̒����̔���]�ŕ\��
//----------------------------------------------------------------------------
class AABB
{
public:
	//!@brief	�R���X�g���N�^
	AABB();
	//!@brief	�R���X�g���N�^
	//!@param[in]	centerPos	���S�_
	//!@param[in]	sideHalfLength	�e���̕ӂ̔����̒���
	AABB(const Math::Vector3& centerPos, const Math::Vector3& sideHalfLength);
public:
	//!@brief	X���̕ӂ̒����̎擾
	//!@return	x���̒���
	const float&	GetLengthX() const;
	//!@brief	Y���̕ӂ̒����̎擾
	//!@return	y���̒���
	const float&	GetLengthY() const;
	//!@brief	Z���̕ӂ̒����̎擾
	//!@return	z���̒���
	const float&	GetLengthZ() const;
	//!@brief	���S���W�̎擾
	//!@return	���S���W(x,y,z)
	const Math::Vector3&	GetCenterPos() const;
public:
	//!@brief	���㉜�̍��W�̎擾
	const Math::Vector3&	GetLeftUpBackPos() const;
	//!@brief	�����O�̍��W�̎擾
	const Math::Vector3&	GetLeftUpFrontPos() const;
	//!@brief	�������̍��W�̎擾
	const Math::Vector3&	GetLeftDownBackPos() const;
	//!@brief	������O�̍��W�̎擾
	const Math::Vector3&	GetLeftDownFrontPos() const;
	//!@brief	�E�㉜�̍��W�̎擾
	const Math::Vector3&	GetRightUpBackPos() const;
	//!@brief	�E���O�̍��W�̎擾
	const Math::Vector3&	GetRightUpFrontPos() const;
	//!@brief	�E�����̍��W�̎擾
	const Math::Vector3&	GetRightDownBackPos() const;
	//!@brief	�E����O�̍��W�̎擾
	const Math::Vector3&	GetRightDownFrontPos() const;
public:
	//!@brief	�����Ƃ̓����蔻��
	//!@param[in]	segment	����
	bool	HitSegment(Segment& segment);
private:
	AABBData		data;
};

