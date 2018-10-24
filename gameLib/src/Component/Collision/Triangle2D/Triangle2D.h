#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Triangle2D
//!@brief	�O�p�`(2D)���`
//!@brief	[�_]��3�p�ӂ��ĕ\��
//----------------------------------------------------------------------------
class Triangle2D
{
public:
	//!@brief	�R���X�g���N�^
	Triangle2D();
	//!@brief	�R���X�g���N�^
	//!@param[in]	point1	�_1
	//!@param[in]	point2	�_2
	//!@param[in]	point3	�_3
	Triangle2D(const Math::Vector2& point1, const Math::Vector2& point2, const Math::Vector2& point3);
public:
	//!@brief	�ӂ̒������擾
	//!@param[in]	vectorNo	�x�N�g��No
	//!@return	�ӂ̒���
	const float	GetLength(int vectorNo) const;
	//!@brief	�Ӄx�N�g��(�񐳋K��)���擾
	//!@param[in]	vectorNo	�x�N�g��No
	//!@return	�Ӄx�N�g��
	const Math::Vector2&	GetVector(int vectorNo) const;
	//!@brief	���_�̎擾
	//!@param[in]	pointNo	���_�ԍ�
	const Math::Vector2&	GetPoint(int pointNo) const;
private:
	Math::Vector2	point[3];
};