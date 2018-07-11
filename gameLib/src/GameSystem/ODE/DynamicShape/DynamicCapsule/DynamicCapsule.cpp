#include "DynamicCapsule.h"
#include "../../src/GameSystem/ODE/Physics/Physics.h"

//!@brief	�R���X�g���N�^
//!@param[in]	centerPos	���S���W
//!@param[in]	direction	����
//!@param[in]	radius		�p�x
//!@param[in]	length		����
//!@param[in]	totalMass	����
DynamicCapsule::DynamicCapsule(const Math::Vector3& centerPos, const int direction, const double radius, const double length, const double& totalMass)
{
	Create();
	SetGeometory(dCreateCapsule(PhysicsWorld::GetPhysics().GetCollisionSpace(), radius, length));
	dGeomSetBody(GetGeometory(), GetRigidBody());
	dBodySetPosition(GetRigidBody(), centerPos.x, centerPos.y, centerPos.z);
}

//!@brief	�R���X�g���N�^
//!@param[in]	dynamicBox	�����̂̍���
DynamicCapsule::DynamicCapsule(const DynamicCapsule& dynamicCapsule)
{
	SetRigidBody(dynamicCapsule.GetRigidBody());
	SetGeometory(dynamicCapsule.GetGeometory());
}

//!@brief	�f�X�g���N�^
DynamicCapsule::~DynamicCapsule()
{

}

//!@brief	�`��̕`��
void	DynamicCapsule::Draw()
{
	//������
}