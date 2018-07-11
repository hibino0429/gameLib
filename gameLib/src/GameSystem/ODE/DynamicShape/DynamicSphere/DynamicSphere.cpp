#include "DynamicSphere.h"
#include "../../src/GameSystem/ODE/Physics/Physics.h"

//!@brief	�R���X�g���N�^
//!@param[in]	centerPos	���S���W
//!@param[in]	radius	���a
//!@param[in]	mass	����
DynamicSphere::DynamicSphere(const Math::Vector3& centerPos, const double& radius, const double& totalMass)
{
	Create();
	dMassSetSphereTotal(ChangeMass(), totalMass, radius);
	dBodySetMass(GetRigidBody(), &GetMass());
	//�W�I���g���̍쐬
	SetGeometory(dCreateSphere(PhysicsWorld::GetPhysics().GetCollisionSpace(),radius));
	//�{�f�B�ɃA�^�b�`
	dGeomSetBody(GetGeometory(), GetRigidBody());
	dBodySetPosition(GetRigidBody(), centerPos.x, centerPos.y, centerPos.z);
}

//!@breif	�R���X�g���N�^
//!@param[in]	dynamicSphere	���̍���
DynamicSphere::DynamicSphere(const DynamicSphere& dynamicSphere)
{
	SetRigidBody(dynamicSphere.GetRigidBody());
	SetGeometory(dynamicSphere.GetGeometory());
}
//!@brief	�f�X�g���N�^
DynamicSphere::~DynamicSphere()
{

}

//!@brief	�`��̕`��
void	DynamicSphere::Draw()
{
	//������
}