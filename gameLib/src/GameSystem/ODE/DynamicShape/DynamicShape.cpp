#include "DynamicShape.h"



//�R���X�g���N�^
DynamicShape::DynamicShape()
{
	rigidBody = dBodyCreate(0);		//������worldID������
	dMassSetZero(&mass);

	Create();
}

//�f�X�g���N�^
DynamicShape::~DynamicShape()
{
	if (geometory != nullptr)
	{
		dGeomDestroy(geometory);
		geometory = nullptr;
	}
	if (rigidBody != nullptr)
	{
		dBodyDestroy(rigidBody);
		rigidBody = nullptr;
	}
}

//!@brief	���̂̍쐬
void		DynamicShape::Create()
{
	SetRigidBody(dBodyCreate(Physics::GetWorld()));
	dMassSetZero(ChangeMass());
}

//!@brief	���W(x,y,z)�̎擾
const Math::Vector3&	DynamicShape::GetPosition() const
{
	const dReal*	pos = dBodyGetPosition(rigidBody);
	return Math::Vector3(static_cast<float>(pos[0]), static_cast<float>(pos[1]), static_cast<float>(pos[2]));
}
//!@brief	���̂̑��x�̎擾
const Math::Vector3&	DynamicShape::GetVelocity() const
{
	const dReal*	vel = dBodyGetLinearVel(rigidBody);
	return Math::Vector3(static_cast<float>(vel[0]), static_cast<float>(vel[1]), static_cast<float>(vel[2]));
}
//!brief	���̂̎p���̉�]�s��̎擾
const dMatrix4&		DynamicShape::GetRotationMatrix() const
{
	dMatrix4	rotateMatrix;
	return rotateMatrix;
}

//!@brief	���W�̐ݒ�
void	DynamicShape::SetPosition(const Math::Vector3& position)
{
	dBodySetPosition(rigidBody, position.x, position.y, position.z);
}
//!@brief	�C�ӎ�1�ɑ΂��Ă̎p���̐ݒ�
void	DynamicShape::SetAxisAngle()
{
	//������
}

//!@brief	�{�f�B�̏d�S�ɍ�p����͂̐ݒ�
//!@brief	���̂��Ƃɏd�͂�������
//!@param[in]	force	�����ɑ΂��Ă̗^�����
void	DynamicShape::AddForce(const Math::Vector3& force)
{
	dBodyAddForce(rigidBody, force.x, force.y, force.z);
}
//!@brief	���̂ɑ��x��^����
//!@param[in]	�����ɑ΂��Ă̗^���鑬�x
void	DynamicShape::AddVelocity(const Math::Vector3& velocity)
{
	dBodySetLinearVel(rigidBody, velocity.x, velocity.y, velocity.z);
}
//!@brief	���̂̕������Z�̃t���O��ݒ肷��
//!@param[in]	physicsOperationFlag	�������Z�̗L��(true)/����(false)�t���O
void	DynamicShape::SetPhysicsOperation(bool physicsOperationFlag)
{
	if (physicsOperationFlag)
	{
		dBodyEnable(rigidBody);
	}
	else
	{
		dBodyDisable(rigidBody);
	}
}


////////////////////////////////////////////////////////////////////
//�擾����
////////////////////////////////////////////////////////////////////
//!@brief	���̂̎擾
const dBodyID&	DynamicShape::GetRigidBody() const
{
	return rigidBody;
}
//!@brief	�Փˌ��m(�W�I���g��)�̎擾
const dGeomID&	DynamicShape::GetGeometory() const
{
	return geometory;
}
//!@brief	���ʂ̎擾
const dMass&	DynamicShape::GetMass() const
{
	return mass;
}
//!@brief	���ʂ̎擾(���ʂ̕ύX��)
dMass*		DynamicShape::ChangeMass()
{
	return &mass;
}

////////////////////////////////////////////////////////////////////
//�ݒ菈��
////////////////////////////////////////////////////////////////////
//!@brief	���̂̐ݒ�
void		DynamicShape::SetRigidBody(const dBodyID& rigidBody)
{
	this->rigidBody = rigidBody;
}
//!@brief	�Փˌ��m(�W�I���g��)�̐ݒ�
void		DynamicShape::SetGeometory(const dGeomID& geometory)
{
	this->geometory = geometory;
}
//!@brief	���ʂ̐ݒ�
void		DynamicShape::SetMass(const dMass& mass)
{
	this->mass = mass;
}