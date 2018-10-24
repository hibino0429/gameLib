#pragma once
#include "../../src/GameSystem/ODE/DynamicShape/DynamicShape.h"

//------------------------------------------------------------------------------
//!@class		DynamicCylinder
//!@brief	�~���̍��̃N���X
//!@brief	��ɉ~���̍��̂������܂�
//------------------------------------------------------------------------------
class DynamicCylinder : public DynamicShape
{
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	centerPos	���S���W
	//!@param[in]	direction	����
	//!@param[in]	radius		�p�x
	//!@param[in]	length		����
	//!@param[in]	mass		����
	DynamicCylinder(const Math::Vector3& centerPos, const int direction,const double radius,const double length, const double& mass);
	//!@brief	�R���X�g���N�^
	//!@param[in]	dynamicBox	�����̂̍���
	DynamicCylinder(const DynamicCylinder& dynamicCylinder);
	//!@brief	�f�X�g���N�^
	~DynamicCylinder();
public:
	//!@brief	�`��̕`��
	void	Draw() override;
};
