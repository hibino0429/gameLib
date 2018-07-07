#include "Physics.h"

//!@brief �R���X�g���N�^
Physics::Physics()
{
	dInitODE();					//ODE�̏�����
	world = dWorldCreate();		//ODE���E�̍쐬

	horizonGravity = 0.0f;
	verticalGravity = -9.81f;
	deepGravity = 0.0f;
	//�d�͐ݒ�
	dWorldSetGravity(world, horizonGravity, verticalGravity, deepGravity);
	//�O���[�o��CFM
	dWorldSetCFM(world, 1e-5);
	dWorldSetContactMaxCorrectingVel(world, 0.1);
	//�O���[�o��ERP
	dWorldSetERP(world, 0.8f);

	//��C��R(���s�ړ����x)
	dWorldSetLinearDamping(world, 0.00001);
	//��C��R(�p���x)
	dWorldSetAngularDamping(world, 0.005);
	//�ő�p���x
	dWorldSetMaxAngularSpeed(world, 200);
	//�ڐG�w�̌���
	dWorldSetContactSurfaceLayer(world, 0.05);
	//���΂炭�����Ȃ�body��������disable����
	dWorldSetAutoDisableFlag(world, 1);

	stepTime = 0.05f;	//�X�e�b�v����
	
	//�Փˌ��o�v�Z
	collisionSpace = dHashSpaceCreate(0);
	//�ڐG�_�̏W�܂���i�[
	jointGroup = dJointGroupCreate(0);
}
//!@brief �f�X�g���N�^
Physics::~Physics()
{
	dJointGroupDestroy(jointGroup);
	dSpaceDestroy(collisionSpace);
	dWorldDestroy(world);
	dCloseODE();
}

//!@brief �������E�̎擾
//!@return �������E
dWorldID		Physics::GetWorld() const
{
	return world;
}
//!@brief ODE��Ԃ̎擾
//!@return ODE�̋��
dSpaceID		Physics::GetCollisionSpace() const
{
	return collisionSpace;
}
//!@brief �W���C���g�O���[�v�̎擾
//!@return �W���C���g�O���[�v
dJointGroupID	Physics::GetJointGroupID() const
{
	return jointGroup;
}


//�T�v: ���͊w�v�Z�̎��{
void	Physics::WorldStep()
{
	dWorldStep(world, stepTime);
}