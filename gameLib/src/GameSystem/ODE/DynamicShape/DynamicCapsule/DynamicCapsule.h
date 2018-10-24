#pragma once
#include "../../src/GameSystem/ODE/DynamicShape/DynamicShape.h"


//------------------------------------------------------------------------------
//!@class		DynamicCapsule
//!@brief	�J�v�Z���̍��̃N���X
//!@brief	��ɃJ�v�Z���̍��̂������܂�
//------------------------------------------------------------------------------
class DynamicCapsule : public DynamicShape
{
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	centerPos	���S���W
	//!@param[in]	direction	����
	//!@param[in]	radius		�p�x
	//!@param[in]	length		����
	//!@param[in]	totalMass	����
	DynamicCapsule(const Math::Vector3& centerPos, const int direction,const double radius,const double length, const double& totalMass);
	//!@brief	�R���X�g���N�^
	//!@param[in]	dynamicBox	�����̂̍���
	DynamicCapsule(const DynamicCapsule& dynamicCapsule);
	//!@brief	�f�X�g���N�^
	~DynamicCapsule();
public:
	//!@brief	�`��̕`��
	void	Draw() override;
};
