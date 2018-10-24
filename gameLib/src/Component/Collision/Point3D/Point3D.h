#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Point3D
//!@brief	3D��Ԃɓ_���`����
//!@brief	[x,y,z]�̍��W�œ_��\��
//----------------------------------------------------------------------------
class Point3D : public Math::Vector3
{
public:
	//!@brief	�R���X�g���N�^
	Point3D();
	//!@brief	�R���X�g���N�^
	//!@param[in]	point	�_
	Point3D(const Math::Vector3& point);
	//!@brief	�R���X�g���N�^
	//!@param[in]	x	���Wx
	//!@param[in]	y	���Wy
	//!@param[in]	z	���Wz
	Point3D(const float x, const float y, const float z);
public:
	//!@brief	�_���W�̎擾
	//!@return	�_�̍��W
	const Math::Vector3&	GetPointPos() const;
};