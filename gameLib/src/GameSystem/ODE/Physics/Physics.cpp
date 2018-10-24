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

//!@brief	�X�e�b�v���Ԃ̎擾
float	Physics::GetStepTime() const
{
	return stepTime;
}







int		PhysicsWorld::num = 0;
int		PhysicsWorld::preNum = 0;
Physics*PhysicsWorld::physicsWorld = nullptr;


//!@brief	��������������Ԃ�K�p
//!@param[in]	physics	�������
void	PhysicsWorld::Attach(Physics* physics)
{
	physicsWorld = physics;
}
//!@brief	�Փˌ��m�̃R�[���o�b�N
//!@param[in]	data	�Փ˃f�[�^
//!@param[in]	col		���g�̕���
//!@param[in]	col2	����̕���
void	PhysicsWorld::NearCallBack(void* data, dGeomID geometory1, dGeomID geometory2)
{
	dBodyID	body1 = dGeomGetBody(geometory1);
	dBodyID body2 = dGeomGetBody(geometory2);
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
	num = dCollide(geometory1, geometory2, contactNum, &contact[0].geom, sizeof(dContact));
	if (num > 0)
	{
		for (int i = 0; i < num; ++i)
		{
			//�Փ˔���
			dJointID jointID = dJointCreateContact(physicsWorld->GetWorld(), physicsWorld->GetJointGroupID(), contact + i);
			//�ڐG�W���C���g����
			dJointAttach(jointID, body1, body2);
		}
	}
}

//!@brief	�X�V
void	PhysicsWorld::UpDate()
{
	dSpaceCollide(physicsWorld->GetCollisionSpace(), 0, &PhysicsWorld::NearCallBack);
	dWorldStep(physicsWorld->GetWorld(), physicsWorld->GetStepTime());
	dJointGroupEmpty(physicsWorld->GetJointGroupID());
}

//!@brief	�Փ˂������𔻒肷��
bool	PhysicsWorld::Hit()
{
	if (num > 0)
	{
		preNum = num;
		num = 0;
		return true;
	}
	return false;
}

//!@brief	1�O�̏Փ˂������������`�F�b�N
bool	PhysicsWorld::PreHit()
{
	if (preNum > 0)
	{
		return true;
	}
	return false;
}

//!@brief	�ێ����Ă��镨����Ԃ��擾����
//!@return	�������
Physics&	PhysicsWorld::GetPhysics()
{
	return *physicsWorld;
}