#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Circle2D
//!@brief	�~(2D)���`
//!@brief	[���S�_]��[���a]�݂̂�����
//----------------------------------------------------------------------------
class Circle2D
{
public:
	//!@brief	�R���X�g���N�^
	Circle2D();
	//!@brief	�R���X�g���N�^
	//!@param[in]	centerPos	���S�_
	//!@param[in]	radius	���a
	Circle2D(const Math::Vector2& centerPos, const float radius);
public:
	//!@brief	���S�_�̎擾
	//!@return	���S�_
	const Math::Vector2&	GetCenterPos() const;
	//!@brief	���a�̎擾
	//!@return	���a
	const float		GetRadius() const;
	//!@brief	���S�_�̃I�t�Z�b�g
	//!@param[in]	offsetVolume	�I�t�Z�b�g��
	void	OffsetCenterPos(const Math::Vector2& offsetVolume);
private:
	Math::Vector2	centerPos;
	float			radius;
};