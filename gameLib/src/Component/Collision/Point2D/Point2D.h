#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Point2D
//!@brief	�_���`
//!@brief	[�_]������
//----------------------------------------------------------------------------
class Point2D
{
public:
	//!@brief	�R���X�g���N�^
	Point2D();
	//!@brief	�R���X�g���N�^
	//!@param[in]	point	�_
	Point2D(const Math::Vector2& point);
public:
	//!@brief	�_�̎擾
	//!@return	�_
	const Math::Vector2&	GetPoint() const;
	//!@brief	�_�Ɠ_�̓����蔻��
	//!@param[in]	targetPoint	���葤�̓_
	//!@return	true: �Փ� false: �Փ˂��Ă��Ȃ�
	bool	Hit(const Point2D& targetPoint);
private:
	Math::Vector2	point;
	float			permissible;	//���e�͈�
};
