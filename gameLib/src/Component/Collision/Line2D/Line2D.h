#pragma once
#include <string>
#include <iostream>
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/GameSystem/ECS/Component/Component.h"


//----------------------------------------------------------------------------
//!@class		Line2D
//!@brief	����(�����ɐL�т���)���`
//!@brief	[1�̓_]��[�����x�N�g��]������
//----------------------------------------------------------------------------
class Line2D
{
public:
	//!@brief	�R���X�g���N�^
	Line2D();
	//!@brief	�R���X�g���N�^
	//!@param[in]	point		�_
	//!@param[in]	dirVector	�����x�N�g��
	Line2D(const Math::Vector2& point, const Math::Vector2& dirVector);
public:
	//!@brief	�_��̍��W���擾
	//!@param[in]	t	�x�N�g���ɂ�����W��
	//!@return	�_�̍��W
	const Math::Vector2&	GetPoint(const float t) const;
private:
	Math::Vector2	point;		//�_
	Math::Vector2	dirVector;	//�����x�N�g��
};

