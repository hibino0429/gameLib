#pragma once
#include "../../src/GameSystem/ODE/DynamicShape/DynamicShape.h"

//------------------------------------------------------------------------------
//!@class		DynamicSphere
//!@brief	���̂̍��̃N���X
//!@brief	��ɋ��̂̍��̂������܂�
//------------------------------------------------------------------------------
class DynamicSphere : public DynamicShape
{
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	centerPos	���S���W
	//!@param[in]	radius		���a
	//!@param[in]	totalMass	����
	DynamicSphere(const Math::Vector3& centerPos, const double& radius, const double& totalMass);
	//!@breif	�R���X�g���N�^
	//!@param[in]	dynamicSphere	���̍���
	DynamicSphere(const DynamicSphere& dynamicSphere);
	//!@brief	�f�X�g���N�^
	~DynamicSphere();

public:
	//!@brief	�`��̕`��
	void	Draw();
};
