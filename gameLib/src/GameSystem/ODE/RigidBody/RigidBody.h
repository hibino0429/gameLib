#pragma once
#include "../../src/GameSystem/ODE/DynamicShape/DynamicShape.h"


//�C���ӏ�
//�ˑ����̂Ȃ����w���C�u�������쐬���A�K�p������K�v������

//----------------------------------------------------------------------------------------
//!@class		RigidBody
//!@brief	���̂������N���X
//!@brief	�K�p�����邱�Ƃŕ��������������邱�Ƃ��ł���
//!@brief	���̂̌`��(dynamicShape)�̉�����s��
//----------------------------------------------------------------------------------------
class RigidBody
{
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	dynamicShape	�`��
	RigidBody(DynamicShape* dynamicShape);
	//!@brief	�f�X�g���N�^
	//!@brief	�`��̉���ӔC������
	virtual ~RigidBody();
public:
	//!@brief	���̂̎擾
	//!@return	�ێ����Ă��鍄�̂̌`���Ԃ�
	DynamicShape&	GetShape() const;

	//�A���C�����g�΍�
	void*	operator new(size_t size)
	{
		return _mm_malloc(size, 16);
	}
	void	operator delete(void* p)
	{
		_mm_free(p);
	}
private:
	DynamicShape*	dynamicShape;	//���̂̌`��
};

