#include "DynamicBox.h"
#include "../../src/GameSystem/ODE/Physics/Physics.h"


//!@brief	�R���X�g���N�^
//!@param[in]	centerPos	���S���W
//!@param[in]	scale	��1�ӂ̑傫��
//!@param[in]	mass	����
DynamicBox::DynamicBox(const Math::Vector3& centerPos, const Math::Vector3& scale, const double& totalMass)
{
	Create();
	dMassSetBoxTotal(ChangeMass(), totalMass, scale.x, scale.y, scale.z);
	dBodySetMass(GetRigidBody(), ChangeMass());
	SetGeometory(dCreateBox(Physics::GetCollisionSpace(),scale.x, scale.y, scale.z));
	dGeomSetBody(GetGeometory(), GetRigidBody());
	dBodySetPosition(GetRigidBody(), centerPos.x, centerPos.y, centerPos.z);
}

//!@brief	�R���X�g���N�^
//!@param[in]	dynamicBox	�����̂̍���
DynamicBox::DynamicBox(const DynamicBox& dynamicBox)
{
	SetRigidBody(dynamicBox.GetRigidBody());
	SetGeometory(dynamicBox.GetGeometory());
}
//!@brief	�f�X�g���N�^
DynamicBox::~DynamicBox()
{

}


//!@brief	�`��̕`��
void	DynamicBox::Draw()
{
	//������
}