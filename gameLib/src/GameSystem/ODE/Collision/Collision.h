#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define warning (disable : 4819)	

#include <ode/ode.h>

#if defined(_DEBUG)
#pragma comment(lib,"oded.lib")
#else
#pragma comment(lib,"ode.lib")
#endif

#include "../../src/GameSystem/ODE/DynamicShape/DynamicShape.h"
#include "../../src/GameSystem/ODE/Physics/Physics.h"

//----------------------------------------------------------------------------------------
//!@class		Collision
//!@brief	�R���W�����������N���X
//!@brief	�Փ˔�����s���`��
//----------------------------------------------------------------------------------------
class Collision
{
public:
	//!@brief	�R���X�g���N�^
	Collision();
	//!@brief	�R���X�g���N�^
	//!@param[in]	dynamicShape	�`��
	Collision(DynamicShape* dynamicShape);
	//!@brief	�f�X�g���N�^
	~Collision();
public:
	//!@brief	�`��̎擾
	//!@return	�ێ����Ă���`��
	const DynamicShape&	GetDynamicShape() const;

public:
	//!@brief	�Փ˂������𔻒�
	//!@brief	�R���W�������m���G�ꂽ�u��
	//!@param[in]	collision	����̃R���W����
	//!@return	true: �Փ˂��� false: �Փ˂��Ă��Ȃ�
	bool	OnCollisionEnter(Collision* collision);
	//!@brief	�Փ˂��Ă��邩�𔻒�
	//!@brief	�R���W�������m���G��Ă����
	//!@return	true: �Փ˂��Ă��� false: �Փ˂��Ă��Ȃ�
	bool	OnCollisionStay(Collision* collision);
	//!@brief	�Փ˂���߂����𔻒�
	//!@brief	�R���W�������m�����ꂽ�Ƃ�
	//!@return	true: �Փ˂��Ȃ��Ȃ��� false: �Փ˂��Ă���
	bool	OnCollisionExit(Collision* collision);
private:
	DynamicShape*			dynamicShape;
};