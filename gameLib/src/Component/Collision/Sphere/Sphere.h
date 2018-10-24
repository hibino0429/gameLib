#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/Point3D/Point3D.h"

//----------------------------------------------------------------------------
//!@class		Sphere
//!@brief	3D��Ԃŋ��̂��`����
//!@brief	[���S�_]��[���a]�ŕ\��
//----------------------------------------------------------------------------
class Sphere
{
public:
	//!@brief	�R���X�g���N�^
	Sphere();
	//!@brief	�R���X�g���N�^
	//!@param[in]	centerPos	���S�_
	//!@param[in]	radius	���a
	Sphere(const Point3D& centerPoint, const float radius);
public:
	//!@brief	���S�_�̎擾
	//!@return	���a(Point3D)
	const Point3D&	GetCenterPoint() const;
	//!@brief	���a�̎擾
	//!@return	���a(float)
	const float		GetRadius() const;
private:
	Point3D		point;
	float		radius;
};