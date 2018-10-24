#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Collision/Segment2D/Segment2D.h"

//----------------------------------------------------------------------------
//!@class		Capsule2D
//!@brief	�J�u�Z��(2D)���`
//!@brief	������𔼌a�̋����X�E�B�[�v�����}�`
//!@brief	[����]��[���a]������
//----------------------------------------------------------------------------
class Capsule2D
{
public:
	//!@brief	�R���X�g���N�^
	Capsule2D();
	//!@brief	�R���X�g���N�^
	//!@param[in]	segment	����
	//!@param[in]	radius	���a
	Capsule2D(const Segment2D& segment, const float radius);
	//!@brief	�R���X�g���N�^
	//!@param[in]	beginPoint	�n�_
	//!@param[in]	endPoint	�I�_
	//!@param[in]	radius	���a
	Capsule2D(const Math::Vector2& beginPoint, const Math::Vector2& endPoint, const float radius);
private:
	Segment2D	segment;
	float		radius;
};