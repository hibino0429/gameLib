#include "DynamicCylinder.h"
#include "../../src/GameSystem/ODE/Physics/Physics.h"

//!@brief	�R���X�g���N�^
//!@param[in]	centerPos	���S���W
//!@param[in]	direction	����
//!@param[in]	radius		�p�x
//!@param[in]	length		����
//!@param[in]	mass		����
DynamicCylinder::DynamicCylinder(const Math::Vector3& centerPos, const int direction, const double radius, const double length, const double& mass)
{
	Create();
	SetGeometory(dCreateCylinder(Physics::GetCollisionSpace(), radius, length));
	dGeomSetBody(GetGeometory(), GetRigidBody());
	dBodySetPosition(GetRigidBody(), centerPos.x, centerPos.y, centerPos.z);
}
//!@brief	�R���X�g���N�^
//!@param[in]	dynamicBox	�����̂̍���
DynamicCylinder::DynamicCylinder(const DynamicCylinder& dynamicCylinder)
{
	SetRigidBody(dynamicCylinder.GetRigidBody());
	SetGeometory(dynamicCylinder.GetGeometory());
}
//!@brief	�f�X�g���N�^
DynamicCylinder::~DynamicCylinder()
{

}

//!@brief	�`��̕`��
void	DynamicCylinder::Draw()
{
	//������
}