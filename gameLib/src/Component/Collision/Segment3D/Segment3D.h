#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/Line3D/Line3D.h"


//----------------------------------------------------------------------------
//!@class		Segment3D
//!@brief	3D��ԂŐ������`���܂�
//!@brief	[�n�_]��[�I�_]��[�n�_]��[�����x�N�g��]�ŕ\��
//----------------------------------------------------------------------------
class Segment3D
{
public:
	//!@brief	�R���X�g���N�^
	Segment3D();
	//!@brief	�R���X�g���N�^
	//!@param[in]	beginPoint	�n�_
	//!@param[in]	vector	�����x�N�g��
	Segment3D(const Point3D& beginPoint, const Math::Vector3& vector);
	//!@brief	�R���X�g���N�^
	//!@param[in]	beginPoint	�n�_
	//!@param[in]	endPoint	�I�_
	Segment3D(const Point3D& beginPoint, const Point3D& endPoint);
public:
	//!@brief	�n�_�̎擾
	//!@return	�n�_(Point3D)
	const Point3D&	GetBeginPoint() const;
	//!@brief	�I�_�̎擾
	//!@return	�I�_(Point3D)
	const Point3D&	GetEndPoint() const;
	//!@brief	�����x�N�g���̎擾
	//!@return	�����x�N�g��(Math::Vector3)
	const Math::Vector3&	GetVector() const;
private:
	Line3D	line;
};