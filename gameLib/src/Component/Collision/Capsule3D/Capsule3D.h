#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/Segment3D/Segment3D.h"

//----------------------------------------------------------------------------
//!@class		Capsule3D
//!@brief	3D��ԂŃJ�v�Z�����`����
//!@brief	[����]��[���a]���ǉ�����ĕ\��
//----------------------------------------------------------------------------
class Capsule3D
{
public:
	//!@brief	�R���X�g���N�^
	Capsule3D();
	//!@brief	�R���X�g���N�^
	//!@param[in]	segment	����
	//!@param[in]	radius	���a
	Capsule3D(const Segment3D& segment, const float radius);
	//!@brief	�R���X�g���N�^
	//!@param[in]	point1	�_1
	//!@param[in]	point2	�_2
	//!@param[in]	radius	���a
	Capsule3D(const Point3D& point1, const Point3D& point2, const float radius);
public:
	//!@brief	�����̎擾
	//!@return	����
	const Segment3D&	GetSegment() const;
	//!@brief	���a�̎擾
	//!@return	���a
	const float&	GetRadius() const;
private:
	Segment3D	segment;
	float		radius;
};