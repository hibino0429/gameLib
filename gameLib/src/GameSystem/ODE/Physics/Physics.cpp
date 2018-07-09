#include "Physics.h"


dWorldID		Physics::world = nullptr;
dSpaceID		Physics::collisionSpace = nullptr;
dJointGroupID	Physics::contactGroup = nullptr;
float			Physics::stepTime = 0;


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
	contactGroup = dJointGroupCreate(0);
}
//!@brief �f�X�g���N�^
Physics::~Physics()
{
	dJointGroupDestroy(contactGroup);
	dSpaceDestroy(collisionSpace);
	dWorldDestroy(world);
	dCloseODE();
}

//!@brief �������E�̎擾
//!@return �������E
dWorldID		Physics::GetWorld()
{
	return world;
}
//!@brief ODE��Ԃ̎擾
//!@return ODE�̋��
dSpaceID		Physics::GetCollisionSpace()
{
	return collisionSpace;
}
//!@brief �W���C���g�O���[�v�̎擾
//!@return �W���C���g�O���[�v
dJointGroupID	Physics::GetJointGroupID()
{
	return contactGroup;
}


//�T�v: ���͊w�v�Z�̎��{
void	Physics::WorldStep()
{
	dWorldStep(world, stepTime);
}

//!@brief	�X�V
void	Physics::UpDate()
{
	
}


//!@brief	�Փˌ��m
//!@param[in]	data	�Փ˃f�[�^
//!@param[in]	col		���g�̕���
//!@param[in]	col2	����̕���
void	Physics::NearCallBack(void* data, const Collision& col, const Collision& col2)
{
	dBodyID	body1 = dGeomGetBody(col.GetDynamicShape().GetGeometory());
	dBodyID body2 = dGeomGetBody(col2.GetDynamicShape().GetGeometory());
	//�ՓˑΏۂ�����
	if (body1 && body2 && dAreConnectedExcluding(body1, body2, dJointTypeContact))
	{
		return;
	}
	//�ڐG�ӏ��̌������߂�
	static constexpr int contactNum = 10;	//�ڐG�ӏ�
	dContact	contact[contactNum];
	for (int i = 0; i < contactNum; ++i)
	{
		//���̓��m�̐ڐG���̃p�����[�^�̐ݒ�
		contact[i].surface.mode = dContactBounce | dContactSoftCFM;
		contact[i].surface.mu = dInfinity;		//���C�W��
		contact[i].surface.bounce = 0.1f;		//�����W��
		contact[i].surface.soft_cfm = 0.01f;	//CFM�ݒ�
	}

	//�Փˌ��o
	int	num = dCollide(col.GetDynamicShape().GetGeometory(), col2.GetDynamicShape().GetGeometory(), contactNum, &contact[0].geom, sizeof(dContact));
	if (num > 0)
	{
		for (int i = 0; i < num; ++i)
		{
			//�Փ˔���
			dJointID jointID = dJointCreateContact(Physics::GetWorld(), contactGroup, contact + i);
			//�ڐG�W���C���g����
			dJointAttach(jointID, body1, body2);
		}
	}
}

