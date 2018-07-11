#pragma once
#include "../../src/GameSystem/ODE/DynamicShape/DynamicShape.h"
#include "../../src/DXEngine/Math/Math.h"


//------------------------------------------------------------------------------
//!@class		DynamicBox
//!@brief	�����̂̍��̃N���X
//!@brief	��ɒ����̂̍��̂������܂�
//------------------------------------------------------------------------------
class DynamicBox : public DynamicShape
{
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	centerPos	���S���W
	//!@param[in]	scale	��1�ӂ̑傫��
	//!@param[in]	totalMass	����
	DynamicBox(const Math::Vector3& centerPos, const Math::Vector3& scale, const double& totalMass);
	//!@brief	�R���X�g���N�^
	//!@param[in]	dynamicBox	�����̂̍���
	DynamicBox(const DynamicBox& dynamicBox);
	//!@brief	�f�X�g���N�^
	~DynamicBox();
public:
	//!@brief	�`��̕`��
	void	Draw() override;
};
