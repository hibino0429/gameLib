#include "RigidBody.h"
#include "../../src/Utility/Utility.hpp"

//�R���X�g���N�^
RigidBody::RigidBody(DynamicShape* dynamicShape)
{
	this->dynamicShape = dynamicShape;
}

//�f�X�g���N�^
RigidBody::~RigidBody()
{
	Utility::SafeDelete(dynamicShape);
}

//!@brief	���̂̎擾
//!@return	�ێ����Ă��鍄�̂̌`���Ԃ�
DynamicShape&	RigidBody::GetShape() const
{
	return *dynamicShape;
}